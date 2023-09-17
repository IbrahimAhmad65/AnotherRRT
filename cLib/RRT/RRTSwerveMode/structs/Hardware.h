//
// Created by ibrahim on 9/14/23.
//

#ifndef CLIB_HARDWARE_H
#define CLIB_HARDWARE_H
namespace swerve {
    struct Falcon {
    public:
        double kT = .0192;
        double kV = 509.2;


    };
    static double getTorqueFalcon(double rpm) {
        // yes im a bozo i know
        return 50;
    }
}
#endif //CLIB_HARDWARE_H
