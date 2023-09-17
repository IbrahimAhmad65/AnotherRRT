//
// Created by ibrahim on 9/11/23.
//

#ifndef CLIB_SWERVEDYNAMICS_H
#define CLIB_SWERVEDYNAMICS_H

#include "Hardware.h"
#include <valarray>
#include <memory>
#include <vector>
#include "PController.h"
#include "Config.h"
#include "Velocity.h"
#include "SwerveState.h"
#include "ForceNTorque.h"
#include "Operators.h"

namespace swerve {
    double getAngleOfVelocity(const swerve::Velocity &vel) {
        return atan2(vel.vy, vel.vx);
    }

    swerve::Force
    getForceNeeded(const swerve::Velocity &start, const swerve::Velocity &end, double dt,
                   const swerve::SwerveConfig &swerveConfig) {
        swerve::Velocity changeInVel = end - start;
        swerve::Force forceNeeded = {changeInVel.vx * swerveConfig.mass / dt, changeInVel.vy * swerveConfig.mass / dt};
        return forceNeeded;
    }

    swerve::Velocity
    updateModule(swerve::Velocity moduleState, swerve::Force force, double dt,
                 const swerve::SwerveConfig &swerveConfig) {
        swerve::Velocity acceleration = {force.fx / swerveConfig.mass, force.fy / swerveConfig.mass};
        swerve::Velocity velocity = {acceleration.vx * dt, acceleration.vy * dt};
        return {velocity + moduleState};
    }

// circle with radius of this
    double getMaximumForceIndependent(swerve::Velocity moduleState, swerve::SwerveConfig swerveConfig) {
        double magStaticForce = swerveConfig.mu * swerveConfig.mass * 9.81 / 4;
        // TODO maybe not divide i dunno im a bozo
        return fmin(magStaticForce, swerve::getTorqueFalcon(moduleState.vx));
    }

    swerve::ForceNTorque
    getTotalForceFromWheelForces(swerve::Force f0, swerve::Force f1, swerve::Force f2, swerve::Force f3,
                                 swerve::ModulePosition m0, swerve::ModulePosition m1,
                                 swerve::ModulePosition m2, swerve::ModulePosition m3) {
        swerve::Force fTotal = f0 + f1 + f2 + f3;
        // find how much torque is applied, where each force is being applied at each module position


        double torque = (m0 * f0) + (m1 * f1) + (m2 * f2) + (m3 * f3);

        return {fTotal, torque};
    }

    swerve::Force getBestForce(const swerve::Velocity &start, const swerve::Velocity &end, double dt,
                               const swerve::SwerveConfig &swerveConfig) {
        swerve::Force f = getForceNeeded(start, end, dt, swerveConfig);
        double maxR = getMaximumForceIndependent(start, swerveConfig);
        double r = sqrt(f.fx * f.fx + f.fy * f.fy);
        return maxR > r ? f : f * (maxR / r);
    }

    swerve::Velocity
    getAverageVelocity(const swerve::Velocity &v0, const swerve::Velocity &v1, const swerve::Velocity &v2,
                       const swerve::Velocity &v3) {
        return (v0 + v1 + v2 + v3) * 0.25;
    }

    swerve::RandomForces
    getRandomForcesForModule(const swerve::Velocity &moduleState, const swerve::SwerveConfig &swerveConfig,
                             int numRandomForces) {
        double maxR = getMaximumForceIndependent(moduleState, swerveConfig);
        swerve::RandomForces randomForces;
        randomForces.forces.reserve(numRandomForces);
        for (int i = 0; i < numRandomForces; ++i) {
            double r = sqrt(((double) rand()) / RAND_MAX);
            double rho = ((double) rand()) * 2 * 3.1415;
            double x = r * cos(rho);
            double y = r * sin(rho);
            randomForces.forces.push_back(std::make_shared<swerve::Force>(swerve::Force{x * maxR, y * maxR}));
        }
        return randomForces;
    }

    swerve::SwerveState
    getUpdatedSwerveState(const swerve::SwerveState &swerveState, const std::vector<swerve::Force> &forces,
                          const swerve::SwerveConfig &swerveConfig, double dt) {
        swerve::SwerveState newSwerveState = swerveState;
        ForceNTorque forceNTorque = getTotalForceFromWheelForces(forces[0], forces[1], forces[2], forces[3],
                                                                 swerveConfig.m0,
                                                                 swerveConfig.m1,
                                                                 swerveConfig.m2,
                                                                 swerveConfig.m3);
        swerve::Velocity module0Vel = updateModule(swerveState.m0, forceNTorque.f, dt, swerveConfig);
        swerve::Velocity module1Vel = updateModule(swerveState.m1, forceNTorque.f, dt, swerveConfig);
        swerve::Velocity module2Vel = updateModule(swerveState.m2, forceNTorque.f, dt, swerveConfig);
        swerve::Velocity module3Vel = updateModule(swerveState.m3, forceNTorque.f, dt, swerveConfig);
        newSwerveState.m0 = module0Vel;
        newSwerveState.m1 = module1Vel;
        newSwerveState.m2 = module2Vel;
        newSwerveState.m3 = module3Vel;
        Velocity avg = getAverageVelocity(module0Vel, module1Vel, module2Vel, module3Vel);
        newSwerveState.firstDerivative = plus(newSwerveState.firstDerivative, avg);
        newSwerveState.firstDerivative.theta += forceNTorque.torque / swerveConfig.inertia;

        newSwerveState.position = plus(newSwerveState.position, avg * .5 * dt * dt);
        newSwerveState.position.theta += forceNTorque.torque / swerveConfig.inertia * .5 * dt * dt;
        newSwerveState.m0 = module0Vel;
        newSwerveState.m1 = module1Vel;
        newSwerveState.m2 = module2Vel;
        newSwerveState.m3 = module3Vel;
        return newSwerveState;


    }


}

#endif //CLIB_SWERVEDYNAMIC