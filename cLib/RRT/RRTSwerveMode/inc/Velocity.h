//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_VELOCITY_H
#define CLIB_VELOCITY_H

#include <valarray>
#include "ModulePosition.h"

namespace swerve{
    struct Velocity {
        double vx;
        double vy;

        Velocity operator+(const Velocity &other) const {
            return {vx + other.vx, vy + other.vy};
        }
        Velocity operator-(const Velocity &other) const {
            return {vx - other.vx, vy - other.vy};
        }
        Velocity operator*(double scalar) const {
            return {vx * scalar, vy * scalar};
        }
        double operator*(const Velocity &other) const {
            return vx * other.vx + vy * other.vy;
        }
        double operator*(swerve::ModulePosition &other) const {
            return vx * other.x + vy * other.y;
        }
        [[nodiscard]] double getMagnitude() const {
            return sqrt(vx * vx + vy * vy);
        }
    };
}
#endif //CLIB_VELOCITY_H
