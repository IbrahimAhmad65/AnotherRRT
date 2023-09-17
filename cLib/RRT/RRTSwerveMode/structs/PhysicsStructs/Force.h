//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_FORCE_H
#define CLIB_FORCE_H

#include "../dynamics_structs/ModulePosition.h"

namespace swerve{
    struct Force {
        double fx;
        double fy;

        Force operator+(const Force &other) const {
            return {fx + other.fx, fy + other.fy};
        }

        double operator*(const Force &other) const {
            return fx * other.fx + fy * other.fy;
        }

        Force operator*(double scalar) const {
            return {fx * scalar, fy * scalar};
        }


    };
}
#endif //CLIB_FORCE_H
