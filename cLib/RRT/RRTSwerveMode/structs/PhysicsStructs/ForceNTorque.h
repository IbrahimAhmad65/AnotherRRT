//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_FORCENTORQUE_H
#define CLIB_FORCENTORQUE_H

#include <valarray>
#include "Force.h"

namespace swerve {
    struct ForceNTorque {
        Force f;
        double torque;
    };
}
#endif //CLIB_FORCENTORQUE_H
