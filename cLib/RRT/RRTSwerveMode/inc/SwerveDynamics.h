//
// Created by ibrahim on 9/11/23.
//

#ifndef CLIB_SWERVEDYNAMICS_H
#define CLIB_SWERVEDYNAMICS_H

#include "Config.h"
#include "ForceNTorque.h"
#include "Hardware.h"
#include "Operators.h"
#include "PController.h"
#include "SwerveState.h"
#include "Velocity.h"
#include <memory>
#include <valarray>
#include <vector>

namespace swerve {
double getAngleOfVelocity(const swerve::Velocity &vel);
swerve::Force getForceNeeded(const swerve::Velocity &start,
                             const swerve::Velocity &end, double dt,
                             const swerve::SwerveConfig &swerveConfig);
swerve::Velocity updateModule(swerve::Velocity moduleState, swerve::Force force,
                              double dt,
                              const swerve::SwerveConfig &swerveConfig);
// circle with radius of this
double getMaximumForceIndependent(swerve::Velocity moduleState,
                                  swerve::SwerveConfig swerveConfig);
swerve::ForceNTorque getTotalForceFromWheelForces(
    swerve::Force f0, swerve::Force f1, swerve::Force f2, swerve::Force f3,
    swerve::ModulePosition m0, swerve::ModulePosition m1,
    swerve::ModulePosition m2, swerve::ModulePosition m3);
swerve::Force getBestForce(const swerve::Velocity &start,
                           const swerve::Velocity &end, double dt,
                           const swerve::SwerveConfig &swerveConfig);
swerve::Velocity getAverageVelocity(const swerve::Velocity &v0,
                                    const swerve::Velocity &v1,
                                    const swerve::Velocity &v2,
                                    const swerve::Velocity &v3);
swerve::RandomForces
getRandomForcesForModule(const swerve::Velocity &moduleState,
                         const swerve::SwerveConfig &swerveConfig,
                         int numRandomForces);
swerve::SwerveState
getUpdatedSwerveState(const swerve::SwerveState &swerveState,
                      const std::vector<swerve::Force> &forces,
                      const swerve::SwerveConfig &swerveConfig, double dt);

} // namespace swerve

#endif // CLIB_SWERVEDYNAMIC