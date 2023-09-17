//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_POSE_H
#define CLIB_POSE_H

#include "Position.h"
#include "Velocity.h"

namespace swerve {
struct Pose {
  Position p;
  double theta;

  Pose operator-(const Pose &other) const;
  double getMagnitude() const;
  Pose operator*(double scalar) const;
  Pose operator+(const Pose &other) const;
  Pose operator/(double scalar) const;
};
} // namespace swerve
#endif // CLIB_POSE_H
