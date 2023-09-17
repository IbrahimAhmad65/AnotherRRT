//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_POSITION_H
#define CLIB_POSITION_H

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
#endif // CLIB_POSITION_H
