//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_PHYSICSSTRUCTS_H
#define CLIB_PHYSICSSTRUCTS_H

#include <vector>
#include <memory>
#include "SwerveDynamicsStructs.h"

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
        double operator*(swerve::ModulePosition &other) const {
            return fx * other.x + fy * other.y;
        }

    };

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

    struct Position {
        double x;
        double y;
    };

    struct ForceNTorque {
        Force f;
        double torque;
    };

    struct RandomForces {
        std::vector<std::shared_ptr<Force>> forces;
    };
}
#endif //CLIB_PHYSICSSTRUCTS_H
