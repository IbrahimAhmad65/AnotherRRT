//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_CUBICHERMITE_H
#define CLIB_CUBICHERMITE_H

#include <memory>
#include <cmath>

struct Knot {
    double x;
    double vx;
};

struct XYKnot {

    Knot xKnot;
    Knot yKnot;

    XYKnot(Knot xKnot, Knot yKnot) {
        this->xKnot = xKnot;
        this->yKnot = yKnot;
    }

};

struct Cubic {
    double a;
    double b;
    double c;
    double d;
};

double accelMagnitudeFunction(double x, Cubic xCubic, Cubic yCubic);

Cubic createCubicFromKnots(Knot initial, Knot end) {
    double a = 2 * initial.x - 2 * end.x + initial.vx + end.vx;
    double b = -3 * initial.x + 3 * end.x - 2 * initial.vx - end.vx;
    double c = initial.vx;
    double d = initial.x;
    return {a, b, c, d};
}


double getSecondsToTraverse(Cubic xCubic, Cubic yCubic, double maxAccel) {

    double testBound1 = accelMagnitudeFunction(0.0, xCubic, yCubic);
    double testBound2 = accelMagnitudeFunction(1.0, xCubic, yCubic);
    double a = xCubic.a;
    double b = xCubic.b;
    double a1 = yCubic.a;
    double b1 = yCubic.b;
    // Not actually the right number, but has the same x value for all values of a,b
    // a1,b1
    double derivativeOfAccelZero = (-a * b - a1 * b1) / (3 * (a * a + a1 * a1));
    double testMaybe = accelMagnitudeFunction(derivativeOfAccelZero, xCubic, yCubic);
    double maxAccelOfOrignialPath = std::fmax(testBound1, std::fmax(testBound2, testMaybe));

    return maxAccelOfOrignialPath / maxAccel;
}

double accelMagnitudeFunction(double x, Cubic xCubic, Cubic yCubic) {
    return
//    std::sqrt(
            x * x * 36 * (xCubic.a * xCubic.a + yCubic.a * yCubic.a)
            + x * 24 * (xCubic.a * xCubic.b + yCubic.a * yCubic.b)
            + 4 * (xCubic.b * xCubic.b + yCubic.b * yCubic.b)
//            );
            ;
}

#endif //CLIB_CUBICHERMITE_H
