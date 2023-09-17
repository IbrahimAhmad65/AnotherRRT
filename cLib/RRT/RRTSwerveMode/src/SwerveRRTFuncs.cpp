#include "../inc/SwerveRRTFuncs.h"

namespace swerve {

swerve::SwerveState iterateWithController(const swerve::Node &start,
                                          const swerve::Node &end,
                                          const swerve::SwerveConfig &config,
                                          const swerve::RRTConfig &rrtConfig) {

  std::vector<Velocity> velocities =
      getWheelVelocities(config, start.state, end.state);
  std::vector<Force> forces;
  forces.reserve(4);
  //        for (int i = 0; i < 4; i++) {
  //            forces[i] = {velocities[i].vx * config.mass / rrtConfig.dt,
  //            velocities[i].vy * config.mass / rrtConfig.dt};
  //        forces[0] = getBestForce(velocities[i], config);
  //        }
  forces.push_back(
      getBestForce(start.state.m0, velocities[0], rrtConfig.dt, config));
  forces.push_back(
      getBestForce(start.state.m1, velocities[1], rrtConfig.dt, config));
  forces.push_back(
      getBestForce(start.state.m2, velocities[2], rrtConfig.dt, config));
  forces.push_back(
      getBestForce(start.state.m3, velocities[3], rrtConfig.dt, config));
  SwerveState newState =
      getUpdatedSwerveState(start.state, forces, config, rrtConfig.dt);
  return newState;
}

swerve::Node extend(const swerve::Node &start, const swerve::Node &end,
                    const swerve::SwerveConfig &config,
                    const swerve::RRTConfig &rrtConfig) {
  int count = 0;
  SwerveState currentState = start.state;
  //        double dt = rrtConfig.dt;
  while (count < rrtConfig.extendIterations &&
         (currentState.position - end.state.position).getMagnitude() <
             rrtConfig.extendthreshold) {
    currentState = iterateWithController(start, end, config, rrtConfig);
    count++;
  }
  double totalTime = start.cost + count * rrtConfig.dt;
  return {currentState, totalTime, std::make_shared<Node>(start)};
}
} // namespace swerve