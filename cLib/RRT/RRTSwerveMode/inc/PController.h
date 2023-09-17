//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_PCONTROLLER_H
#define CLIB_PCONTROLLER_H

#include <memory>
#include <vector>
#include <valarray>
#include "RandomForces.h"
#include "Position.h"

namespace swerve {


    struct PController {
        double kP;


        [[nodiscard]] double get(double setpoint, double goal) const {
            double error = setpoint - goal;
            double output = kP * error;
            return output;
        }
    };


}
#endif //CLIB_PCONTROLLER_H
