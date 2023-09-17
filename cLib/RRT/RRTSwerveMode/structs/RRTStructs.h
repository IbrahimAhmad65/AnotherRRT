//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_RRTSTRUCTS_H
#define CLIB_RRTSTRUCTS_H

#include "../dynamics_kinematics/SwerveDynamics.h"

namespace swerve {
    struct Node {
        SwerveState state;
        double cost;
        std::shared_ptr<Node> parent;
    };
}
#endif //CLIB_RRTSTRUCTS_H
