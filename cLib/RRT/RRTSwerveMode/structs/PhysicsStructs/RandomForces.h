//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_RANDOMFORCES_H
#define CLIB_RANDOMFORCES_H

#include <vector>
#include <memory>
#include "PController.h"
#include "Force.h"

namespace swerve{
//    struct ModulePosition;
    struct RandomForces {
        std::vector<std::shared_ptr<Force>> forces;
    };
}
#endif //CLIB_RANDOMFORCES_H
