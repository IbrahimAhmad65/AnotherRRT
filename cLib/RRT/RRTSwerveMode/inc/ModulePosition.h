//
// Created by ibrahim on 9/16/23.
//

#pragma once
#include "Force.h"

namespace swerve {
struct ModulePosition {
  double x;
  double y;
  double operator*(Force &force) const;
};
} // namespace swerve
