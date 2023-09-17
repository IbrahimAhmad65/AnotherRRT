//
// Created by ibrahim on 9/17/23.
//

#include "../inc/ForceNTorque.h"

namespace swerve {
    struct ForceNTorque {
        swerve::Force f;
        double torque{};
    };
}