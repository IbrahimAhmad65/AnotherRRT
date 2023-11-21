//
// Created by ibrahim on 9/16/23.
//
#pragma once

#include "Position.h"
#include "Velocity.h"
#include <string>

namespace swerve
{
  struct Pose
  {
    Position p;
    double theta;

    Pose operator-(const Pose &other) const;
    double getMagnitude() const;
    Pose operator*(double scalar) const;
    Pose operator+(const Pose &other) const;
    Pose operator/(double scalar) const;
    std::string toString() const;
  };
} // namespace swerve
