//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVEDRIVEKINEMATICSRRT_H
#define CLIB_SWERVEDRIVEKINEMATICSRRT_H

#include "Config.h"
#include "PController.h"
#include "RandomForces.h"
#include "SwerveState.h"
#include "frc/kinematics/SwerveDriveKinematics.h"
#include <vector>
namespace swerve {

std::vector<swerve::Velocity>
getWheelVelocities(const swerve::SwerveConfig &config,
                   swerve::SwerveState currentState,
                   swerve::SwerveState targetState);
}
#endif // CLIB_SWERVEDRIVEKINEMATICSRRT_H
