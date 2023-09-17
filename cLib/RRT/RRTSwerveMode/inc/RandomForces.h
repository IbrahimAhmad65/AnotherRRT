//
// Created by ibrahim on 9/15/23.
//

#pragma once
#include "Force.h"
#include "PController.h"
#include <memory>
#include <vector>

namespace swerve {
//    struct ModulePosition;
struct RandomForces {
  std::vector<std::shared_ptr<Force>> forces;
};
} // namespace swerve
