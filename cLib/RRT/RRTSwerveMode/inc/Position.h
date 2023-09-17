//
// Created by ibrahim on 9/16/23.
//

#pragma once
#include "RandomForces.h"

namespace swerve {
struct Position {
  double x;
  double y;

  Position operator-(const Position &other) const;
  double operator*(Position &other) const;
  double operator*(Force &other) const;
};
} // namespace swerve
