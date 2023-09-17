//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVEDYNAMICSSTRUCTS_H
#define CLIB_SWERVEDYNAMICSSTRUCTS_H

#include <memory>
#include <vector>
#include <valarray>
#include "frc/kinematics/SwerveDriveKinematics.h"
#include "PhysicsStructs.h"

namespace swerve {


    struct PController {
        double kP;

        explicit PController(double kP) : kP(kP) {}

        double get(double setpoint, double goal) const {
            double error = setpoint - goal;
            double output = kP * error;
            return output;
        }
    };

    struct ModulePosition {
        double x;
        double y;

        ModulePosition operator-(const ModulePosition &other) const {
            return {x - other.x, y - other.y};
        }
        double operator*(swerve::ModulePosition &other) const {
            return x * other.x + y * other.y;
        }
        double operator*(swerve::Force &other) const {
            return x * other.fx + y * other.fy;
        }
    };



    struct Pose {
        Position p;
        double theta;

        Pose operator-(const Pose &other) const {
            return {p.x - other.p.x, p.y - other.p.y, theta - other.theta};
        }

        double getMagnitude() const {
            return sqrt(p.x * p.x + p.y * p.y);
        }
    };


    struct SwerveState {
        Velocity m0;
        Velocity m1;
        Velocity m2;
        Velocity m3;
        Pose position;
        Pose firstDerivative;
    };


}
#endif //CLIB_SWERVEDYNAMICSSTRUCTS_H
