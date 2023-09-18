#include "../inc/ModulePosition.h"

namespace swerve {
double ModulePosition::operator*(Force &force) const {
  return x * force.fx + y * force.fy;
}
} // namespace swerve