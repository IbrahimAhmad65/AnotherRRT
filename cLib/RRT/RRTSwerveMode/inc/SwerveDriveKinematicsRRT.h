//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVEDRIVEKINEMATICSRRT_H
#define CLIB_SWERVEDRIVEKINEMATICSRRT_H

#include <vector>
#include "PController.h"
#include "frc/kinematics/SwerveDriveKinematics.h"
#include "RandomForces.h"
#include "Config.h"
#include "SwerveState.h"

std::vector<swerve::Velocity> getWheelVelocities(const swerve::SwerveConfig &config, swerve::SwerveState currentState,
                                                 swerve::SwerveState targetState) {
    double vxChassis, vyChassis, omega;
    vxChassis = config.xController.get(targetState.position.p.x, currentState.position.p.x);
    vyChassis = config.yController.get(targetState.position.p.y, currentState.position.p.y);
    omega = config.thetaController.get(targetState.position.theta, currentState.position.theta);
    vxChassis += config.vxController.get(targetState.firstDerivative.p.x, currentState.firstDerivative.p.x);
    vyChassis += config.vyController.get(targetState.firstDerivative.p.y, currentState.firstDerivative.p.y);
    omega += config.thetaDotController.get(targetState.firstDerivative.theta, currentState.firstDerivative.theta);
    wpi::array<frc::SwerveModuleState, 4> moduleStates = config.kinematics.ToSwerveModuleStates(
            {units::meters_per_second_t(vxChassis), units::meters_per_second_t(vyChassis), units::radians_per_second_t(omega)});
    std::vector<swerve::Velocity> velocities;
    velocities.reserve(4);
    for (int i = 0; i < 4; i++) {
        double vxModule = moduleStates[i].speed.to<double>() * cos(moduleStates[i].angle.Radians().to<double>());
        double vyModule = moduleStates[i].speed.to<double>() * sin(moduleStates[i].angle.Radians().to<double>());
        velocities.emplace_back(vxModule, vyModule);
    }
    return velocities;
}


#endif //CLIB_SWERVEDRIVEKINEMATICSRRT_H
