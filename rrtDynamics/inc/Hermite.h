#pragma once
#include "Vector.h"
#include <cmath>
namespace pmass {
struct Cubic {
  double a, b, c, d;
};
double accelMagnitudeFunction(double x, Cubic xCubic, Cubic yCubic);

inline Cubic createCubicFromKnots(Vector initial, Vector end)
{
  double a = 2 * initial.x - 2 * end.x + initial.y + end.y;
  double b = -3 * initial.x + 3 * end.x - 2 * initial.y - end.y;
  double c = initial.y;
  double d = initial.x;
  return {a, b, c, d};
}

inline double getSecondsToTraverse(Cubic xCubic, Cubic yCubic, double maxAccel)
{

  double testBound1 = accelMagnitudeFunction(0.0, xCubic, yCubic);
  double testBound2 = accelMagnitudeFunction(1.0, xCubic, yCubic);
  double a = xCubic.a;
  double b = xCubic.b;
  double a1 = yCubic.a;
  double b1 = yCubic.b;
  double derivativeOfAccelZero = (-a * b - a1 * b1) / (3 * (a * a + a1 * a1));
  double testMaybe = accelMagnitudeFunction(derivativeOfAccelZero, xCubic, yCubic);
  double maxAccelOfOrignialPath = std::fmax(testBound1, std::fmax(testBound2, testMaybe));

  return maxAccelOfOrignialPath / maxAccel;
}

inline double accelMagnitudeFunction(double x, Cubic xCubic, Cubic yCubic)
{
  return x * x * 36 * (xCubic.a * xCubic.a + yCubic.a * yCubic.a) + x * 24 * (xCubic.a * xCubic.b + yCubic.a * yCubic.b) + 4 * (xCubic.b * xCubic.b + yCubic.b * yCubic.b);
}
} // namespace pmass