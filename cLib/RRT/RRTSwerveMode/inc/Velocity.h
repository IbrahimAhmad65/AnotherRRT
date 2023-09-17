//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_VELOCITY_H
#define CLIB_VELOCITY_H

#include "ModulePosition.h"
#include <valarray>

namespace swerve {
struct Velocity {
  double vx;
  double vy;

public:
  Velocity operator+(const Velocity &other) const;
  Velocity operator-(const Velocity &other) const;
  Velocity operator*(double scalar) const;
  double operator*(const Velocity &other) const;
  double operator*(swerve::ModulePosition &other) const;
  [[nodiscard]] double getMagnitude() const;
};
} // namespace swerve
#endif // CLIB_VELOCITY_H
