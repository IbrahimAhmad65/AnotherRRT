#include "../inc/PController.h"
namespace swerve {
[[nodiscard]] double PController::get(double setpoint, double goal) const {
  double error = setpoint - goal;
  double output = kP * error;
  return output;
}
} // namespace swerve