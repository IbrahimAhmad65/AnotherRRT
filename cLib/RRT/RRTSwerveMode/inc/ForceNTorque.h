//
// Created by ibrahim on 9/16/23.
//
#pragma once

#include "Force.h"
#include <valarray>

namespace swerve {

struct ForceNTorque {
  swerve::Force f;
  double torque{};
};
} // namespace swerve
