//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_POSE_H
#define CLIB_POSE_H

#include "Velocity.h"
#include "Position.h"

namespace swerve{
    struct Pose {
        Position p;
        double theta;

        Pose operator-(const Pose &other) const {
            return {p.x - other.p.x, p.y - other.p.y, theta - other.theta};
        }

        double getMagnitude() const {
            return sqrt(p.x * p.x + p.y * p.y);
        }
        Pose operator*(double scalar) const {
            return {p.x * scalar, p.y * scalar, theta * scalar};
        }
        Pose operator+(const Pose &other) const {
            return {p.x + other.p.x, p.y + other.p.y, theta + other.theta};
        }
        Pose operator/(double scalar) const {
            return {p.x / scalar, p.y / scalar, theta / scalar};
        }

    };
}
#endif //CLIB_POSE_H
