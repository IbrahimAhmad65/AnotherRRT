#include "../inc/Velocity.h"

namespace swerve {
Velocity Velocity::operator+(const Velocity &other) const {
  return {vx + other.vx, vy + other.vy};
}
Velocity Velocity::operator-(const Velocity &other) const {
  return {vx - other.vx, vy - other.vy};
}
Velocity Velocity::operator*(double scalar) const { return {vx * scalar, vy * scalar}; }
double Velocity::operator*(const Velocity &other) const {
  return vx * other.vx + vy * other.vy;
}
double Velocity::operator*(swerve::ModulePosition &other) const {
  return vx * other.x + vy * other.y;
}
[[nodiscard]] double Velocity::getMagnitude() const { return sqrt(vx * vx + vy * vy); }
} // namespace swerve