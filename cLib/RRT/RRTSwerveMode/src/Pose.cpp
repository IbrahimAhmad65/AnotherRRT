#include "../inc/Pose.h"
namespace swerve {
Pose Pose::operator-(const Pose &other) const {
  return {{p.x - other.p.x, p.y - other.p.y}, theta - other.theta};
}

double Pose::getMagnitude() const { return sqrt(p.x * p.x + p.y * p.y); }
Pose Pose::operator*(double scalar) const {
  return {{p.x * scalar, p.y * scalar}, theta * scalar};
}
Pose Pose::operator+(const Pose &other) const {
  return {{p.x + other.p.x, p.y + other.p.y}, theta + other.theta};
}
Pose Pose::operator/(double scalar) const {
  return {{p.x / scalar, p.y / scalar}, theta / scalar};
}
std::string Pose::toString() const{
  return "x: " + std::to_string(p.x) +  "y: " + std::to_string(p.y);
}
} // namespace swerve