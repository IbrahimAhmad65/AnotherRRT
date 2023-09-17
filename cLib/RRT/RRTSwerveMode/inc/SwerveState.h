//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_SWERVESTATE_H
#define CLIB_SWERVESTATE_H

#include "PController.h"
#include "Pose.h"
#include "Velocity.h"

namespace swerve {
struct SwerveState {
  Velocity m0;
  Velocity m1;
  Velocity m2;
  Velocity m3;
  Pose position;
  Pose firstDerivative;
};
} // namespace swerve
#endif // CLIB_SWERVESTATE_H
