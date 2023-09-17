//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVERRTFUNCS_H
#define CLIB_SWERVERRTFUNCS_H

#include "structs/RRTStructs.h"
#include "structs/Config.h"
#include "dynamics_kinematics/SwerveDriveKinematicsRRT.h"

namespace swerve {
    swerve::Node
    iterateWithController(const swerve::Node &start, const swerve::Node &end, const swerve::SwerveConfig &config,
                          const swerve::RRTConfig &rrtConfig) {

        std::vector<Velocity> velocities = getWheelVelocities(config,start.state, end.state);
        std::vector<Force> forces;
        forces.reserve(4);
        for (int i = 0; i < 4; i++) {
            forces[i] = {velocities[i].vx * config.mass / rrtConfig.dt, velocities[i].vy * config.mass / rrtConfig.dt};
        }

    }


    swerve::Node extend(const swerve::Node &start, const swerve::Node &end, const swerve::SwerveConfig &config,
                        const swerve::RRTConfig &rrtConfig) {
        int count = 0;
        SwerveState currentState = start.state;
        while (count < rrtConfig.extendIterations &&
               (currentState.position - end.state.position).getMagnitude() < rrtConfig.extendthreshold) {

        }


    }


}
#endif //CLIB_SWERVERRTFUNCS_H
