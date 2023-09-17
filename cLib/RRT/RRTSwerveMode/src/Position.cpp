#include "../inc/Position.h"
namespace swerve {
Position Position::operator-(const Position &other) const {
  return {x - other.x, y - other.y};
}

double Position::operator*(Position &other) const {
  return x * other.x + y * other.y;
}

double Position::operator*(Force &other) const {
  return x * other.fx + y * other.fy;
}
} // namespace swerve