#include "../inc/SwerveRRTFuncs.h"
#include <cstdlib>
#include <iostream>
#include <iterator>

namespace swerve {

swerve::SwerveState iterateWithController(const swerve::SwerveState &start,
                                          const swerve::SwerveState &end,
                                          const swerve::SwerveConfig &config,
                                          const swerve::RRTConfig &rrtConfig) {

  std::vector<Velocity> velocities = getWheelVelocities(config, start, end);
  std::vector<Force> forces;
  forces.reserve(4);
  //        for (int i = 0; i < 4; i++) {
  //            forces[i] = {velocities[i].vx * config.mass / rrtConfig.dt,
  //            velocities[i].vy * config.mass / rrtConfig.dt};
  //        forces[0] = getBestForce(velocities[i], config);
  //        }
  forces.push_back(getBestForce(start.m0, velocities[0], rrtConfig.dt, config));
  forces.push_back(getBestForce(start.m1, velocities[1], rrtConfig.dt, config));
  forces.push_back(getBestForce(start.m2, velocities[2], rrtConfig.dt, config));
  forces.push_back(getBestForce(start.m3, velocities[3], rrtConfig.dt, config));

  for (auto k : forces) {
    std::cout << k.fx << " " << k.fy << std::endl;
  }

  SwerveState newState =
      getUpdatedSwerveState(start, forces, config, rrtConfig.dt);
  return newState;
}

swerve::Node extend(const swerve::Node &start, const swerve::Node &end,
                    const swerve::SwerveConfig &config,
                    const swerve::RRTConfig &rrtConfig) {
  int count = 0;
  SwerveState currentState = start.state;
  //        double dt = rrtConfig.dt;
  //   bool loopCheck =
  //       fabs((currentState.position - end.state.position).getMagnitude()) <
  //       rrtConfig.extendthreshold;
  //   std::cout << loopCheck << std::endl;
  //   std::cout << rrtConfig.extendthreshold << std::endl;
  //   std::cout << ((currentState.position - end.state.position).getMagnitude()
  //   >
  //                 .1)
  //             << std::endl;
  while (count < rrtConfig.extendIterations &&
         (currentState.position - end.state.position).getMagnitude() >
             rrtConfig.extendthreshold) {
    std::cout << "HI" << std::endl;
    std::cout << currentState.position.p.x << std::endl;
    currentState =
        iterateWithController(start.state, end.state, config, rrtConfig);
    std::cout << currentState.position.p.x << std::endl;
    count++;
  }
  double totalTime = start.cost + count * rrtConfig.dt;
  return {currentState, std::make_shared<Node>(start), totalTime};
}
} // namespace swerve