//
// Created by ibrahim on 9/17/23.
//
#include "Config.h"
namespace swerve{
    struct RRTConfig {
        int maxIterations;
        int extendIterations;
        double extendthreshold;
        double goalThreshold;
        double dt;
    };

    struct SwerveConfig {
        double mu;
        double mass;
        double inertia;
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
        frc::SwerveDriveKinematics<4> kinematics;

    };
}
