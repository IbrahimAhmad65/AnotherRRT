//
// Created by ibrahim on 9/11/23.
//

#ifndef CLIB_SWERVEDYNAMICS_H
#define CLIB_SWERVEDYNAMICS_H

#include "../structs/Hardware.h"
#include <valarray>
#include <memory>
#include <vector>
#include "../structs/SwerveDynamicsStructs.h"
#include "../structs/Config.h"

namespace swerve {
    double getAngleOfVelocity(const swerve::Velocity &vel) {
        return atan2(vel.vy, vel.vx);
    }

    swerve::Force
    getForceNeeded(swerve::Velocity &start, swerve::Velocity &end, double dt,
                   swerve::SwerveConfig &swerveConfig) {
        swerve::Velocity changeInVel = end - start;
        swerve::Force forceNeeded = {changeInVel.vx * swerveConfig.mass / dt, changeInVel.vy * swerveConfig.mass / dt};
        return forceNeeded;
    }

    swerve::Velocity
    updateModule(swerve::Velocity moduleState, swerve::Force force, double dt, swerve::SwerveConfig &swerveConfig) {
        swerve::Velocity acceleration = {force.fx / swerveConfig.mass, force.fy / swerveConfig.mass};
        swerve::Velocity velocity = {acceleration.vx * dt, acceleration.vy * dt};
        return {velocity + moduleState};
    }

// circle with radius of this
    double getMaximumForceIndependent(swerve::Velocity moduleState, swerve::SwerveConfig swerveConfig) {
        double magStaticForce = swerveConfig.mu * swerveConfig.mass * 9.81 / 4;
        // TODO maybe not divide i dunno im a bozo
        return fmin(magStaticForce, swerve::getTorqueFalcon(moduleState.));
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

    swerve::Force getBestForce(swerve::Velocity &start, swerve::Velocity &end, double dt,
                               swerve::SwerveConfig &swerveConfig) {
        swerve::Force f = getForceNeeded(start, end, dt, swerveConfig);
        double maxR = getMaximumForceIndependent(start, swerveConfig);
        double r = sqrt(f.fx * f.fx + f.fy * f.fy);
        return maxR > r ? f : f * (maxR / r);
    }

    swerve::RandomForces
    getRandomForcesForModule(const swerve::Velocity &moduleState, swerve::SwerveConfig swerveConfig,
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
    swerve::SwerveState getUpdatedSwerveState(const swerve::SwerveState &swerveState, const std::vector<swerve::Force> &forces,
                                              const swerve::SwerveConfig &swerveConfig, double dt) {



    }


}

#endif //CLIB_SWERVEDYNAMIC