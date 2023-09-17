//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_NODE_H
#define CLIB_NODE_H

#include "../dynamics_structs/SwerveState.h"

namespace swerve{
    struct Node{
        SwerveState state;
        std::shared_ptr<Node> parent;
        double cost = 1e307;
    };
}
#endif //CLIB_NODE_H
