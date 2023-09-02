//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_CUBICHERMITE_H
#define CLIB_CUBICHERMITE_H

#include <memory>

struct Knot{
    double x;
    double vx;
};

struct Cubic{
    double a;
    double b;
    double c;
    double d;
};
double computeCubic(Cubic cubic, double t);
Cubic computeCubicHermite(Knot start, Knot end);
double getSecondsToTraverse(Cubic )
#endif //CLIB_CUBICHERMITE_H
