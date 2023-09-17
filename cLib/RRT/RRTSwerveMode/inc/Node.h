//
// Created by ibrahim on 9/16/23.
//
#pragma once

#include "SwerveState.h"

namespace swerve {
struct Node {
  SwerveState state;
  std::shared_ptr<Node> parent;
  double cost = 1e307;
};
} // namespace swerve
