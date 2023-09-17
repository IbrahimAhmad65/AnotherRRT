//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_POSITION_H
#define CLIB_POSITION_H

#include "RandomForces.h"

namespace swerve {
    struct Position {
        double x;
        double y;

        Position operator-(const Position &other) const {
            return {x - other.x, y - other.y};
        }

        double operator*(Position &other) const {
            return x * other.x + y * other.y;
        }

        double operator*(Force &other) const {
            return x * other.fx + y * other.fy;
        }
    };
}
#endif //CLIB_POSITION_H
