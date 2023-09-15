//
// Created by ibrahim on 9/11/23.
//

#ifndef CLIB_SWERVEDYNAMICS_H
#define CLIB_SWERVEDYNAMICS_H

#include "Hardware.h"
#include <valarray>
#include <memory>
#include <vector>
#include "SwerveDynamicsStructs.h"
namespace swerve {
    double getAngleOfVelocity(const swerve::Velocity &vel) {
        return atan2(vel.vy, vel.vx);
    }

    swerve::Force
    getForceNeeded(swerve::ModuleState &start, swerve::ModuleState &end, double dt,
                   swerve::SwerveConfig &swerveConfig) {
        swerve::Velocity changeInVel = end - start;
        swerve::Force forceNeeded = {changeInVel.vx * swerveConfig.mass / dt, changeInVel.vy * swerveConfig.mass / dt};
        return forceNeeded;
    }

    swerve::ModuleState
    updateModule(swerve::ModuleState moduleState, swerve::Force force, double dt, swerve::SwerveConfig &swerveConfig) {
        swerve::Velocity acceleration = {force.fx / swerveConfig.mass, force.fy / swerveConfig.mass};
        swerve::Velocity velocity = {acceleration.vx * dt, acceleration.vy * dt};
        return {velocity + moduleState.velocity};
    }

// circle with radius of this
    double getMaximumForceIndependent(swerve::ModuleState moduleState, swerve::SwerveConfig swerveConfig) {
        double magStaticForce = swerveConfig.mu * swerveConfig.mass * 9.81 / 4;
        // TODO maybe not divide i dunno im a bozo
        return fmin(magStaticForce, swerve::getTorqueFalcon(500));
    }

    swerve::ForceNAngularForce
    getTotalForceFromWheelForces(swerve::Force f0, swerve::Force f1, swerve::Force f2, swerve::Force f3,
                                 swerve::ModulePosition m1, swerve::ModulePosition m2,
                                 swerve::ModulePosition m3, swerve::ModulePosition m4) {
        swerve::Force fTotal = f0 + f1 + f2 + f3;
        // find how much torque is applied, where each force is being applied at each module position
        double torque = f0 * m1 + f1 * m2 + f2 * m3 + f3 * m4;
        return {fTotal, torque};
    }

    swerve::RandomForces
    getRandomForcesForModule(const swerve::ModuleState &moduleState, swerve::SwerveConfig swerveConfig,
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
}

#endif //CLIB_SWERVEDYNAMIC