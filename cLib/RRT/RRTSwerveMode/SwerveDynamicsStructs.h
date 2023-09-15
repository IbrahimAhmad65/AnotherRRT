//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVEDYNAMICSSTRUCTS_H
#define CLIB_SWERVEDYNAMICSSTRUCTS_H

#include <memory>
#include <vector>
#include <valarray>

namespace swerve {
    struct RRTConfig{
        int maxIterations;
        int extendIterations;
        double extendthreshold;
        double goalThreshold;
        double dt;
    };


    struct PController {
        double kP;

        PController(double kP) : kP(kP) {}

        double get(double setpoint, double goal) const {
            double error = setpoint - goal;
            double output = kP * error;
            return output;
        }
    };


    struct ModulePosition {
        double x;
        double y;
    };
    struct SwerveConfig {
        double mu;
        double mass;
        PController xController;
        PController yController;
        PController thetaController;
        PController vxController;
        PController vyController;
        PController thetaDotController;
        ModulePosition m0;
        ModulePosition m1;
        ModulePosition m2;
        ModulePosition m3;

    };


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

        double operator*(const ModulePosition &other) const {
            return fx * other.x + fy * other.y;
        }
    };

    struct Velocity {
        double vx;
        double vy;

        Velocity operator+(const Velocity &other) const {
            return {vx + other.vx, vy + other.vy};
        }
    };

    struct Position {
        double x;
        double y;
    };

    struct ModuleState {
        Velocity velocity;

        Velocity operator-(const ModuleState &other) const {
            return {velocity.vx - other.velocity.vx, velocity.vy - other.velocity.vy};
        }

        Velocity operator*(double scalar) const {
            return {velocity.vx * scalar, velocity.vy * scalar};
        }

        ModuleState operator+(const ModuleState &other) const {
            return {velocity.vx + other.velocity.vx, velocity.vy + other.velocity.vy};
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
    struct ForceNAngularForce {
        Force f;
        double torque;
    };
    struct SwerveState {
        ModuleState m0;
        ModuleState m1;
        ModuleState m2;
        ModuleState m3;
        Pose position;
        Pose firstDerivative;
    };

    struct RandomForces {
        std::vector<std::shared_ptr<Force>> forces;
    };
}
#endif //CLIB_SWERVEDYNAMICSSTRUCTS_H
