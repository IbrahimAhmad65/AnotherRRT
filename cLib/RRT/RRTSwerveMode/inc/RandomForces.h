//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_RANDOMFORCES_H
#define CLIB_RANDOMFORCES_H

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
#endif // CLIB_RANDOMFORCES_H
