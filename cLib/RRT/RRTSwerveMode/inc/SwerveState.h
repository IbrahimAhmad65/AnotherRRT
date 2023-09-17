//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_SWERVESTATE_H
#define CLIB_SWERVESTATE_H

#include "Velocity.h"
#include "PController.h"
#include "Pose.h"

namespace swerve{
    struct SwerveState {
        Velocity m0;
        Velocity m1;
        Velocity m2;
        Velocity m3;
        Pose position;
        Pose firstDerivative;
    };
}
#endif //CLIB_SWERVESTATE_H
