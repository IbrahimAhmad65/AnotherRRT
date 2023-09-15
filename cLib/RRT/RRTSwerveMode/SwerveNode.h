//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVENODE_H
#define CLIB_SWERVENODE_H

#include "SwerveDynamics.h"

namespace swerve {
    struct Node {
        SwerveState state;
        double cost;
        std::shared_ptr<Node> parent;
    };
}
#endif //CLIB_SWERVENODE_H
