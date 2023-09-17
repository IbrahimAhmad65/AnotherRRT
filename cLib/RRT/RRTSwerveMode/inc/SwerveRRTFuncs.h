//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVERRTFUNCS_H
#define CLIB_SWERVERRTFUNCS_H

#include "Config.h"
#include "Node.h"
#include "SwerveDriveKinematicsRRT.h"
#include "SwerveState.h"
#include "Velocity.h"

namespace swerve {
swerve::SwerveState iterateWithController(const swerve::Node &start,
                                          const swerve::Node &end,
                                          const swerve::SwerveConfig &config,
                                          const swerve::RRTConfig &rrtConfig);

swerve::Node extend(const swerve::Node &start, const swerve::Node &end,
                    const swerve::SwerveConfig &config,
                    const swerve::RRTConfig &rrtConfig);

} // namespace swerve
#endif // CLIB_SWERVERRTFUNCS_H
