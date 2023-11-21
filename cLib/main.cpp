#include "Debug/Timer.h"
#include "RRT/Dijkstra/Dijkstra.h"
#include "RRT/Dijkstra/Graph.h"
#include "RRT/RRTPointMass.h"
#include "RRT/RRTSwerveMode/inc/PController.h"
#include "RRT/RRTSwerveMode/inc/SwerveRRTFuncs.h"

#include "RRT/RRTSwerveMode/inc/Config.h"

void rrtPointMassTest() {
  std::vector<Node> path;
  {
    Timer timer;
    //        for (int i = -1; i < 100; ++i) {

    RRTPointMassConfig config = RRTPointMassConfig();
    config.maxX = 2;
    config.maxY = 2;
    config.maxAccel = 9;
    config.maxVel = 1;
    config.radiusOfCompletion = .4;
    config.iterations = 4999;
    config.maxTime = 49;
    Node start = {0, 1, 1, -1};
    Node end = {1, 2, 0, -1};
    path = rrtPointMass(start, end, config);
    //        std::cout << "Path: " << path.size() << std::endl;
    //    printPath(path);
    //        }
  }
  printPath(path);
  //        path[-1] = {0,0,0,0};
  std::cout << "Path: " << path[-1].time << std::endl;
}

void dijkstraTest() {

  Graph g = Graph();
  GraphNode n1 = {0, 0, 0, 0, 1e308, std::vector<Edge>()};
  GraphNode n2 = {1, 0, 3, 2, 1e308, std::vector<Edge>()};
  GraphNode n3 = {1, 5, 6, 2, 1e308, std::vector<Edge>()};
  g.nodes.push_back(n1);
  g.nodes.push_back(n2);
  g.nodes.push_back(n3);
  auto nodes = generateFilledNodes(g.nodes, 1);
  //        g.nodes[0].neighbors.erase(g.nodes[0].neighbors.begin());
  //        std::cout << "Hey" << std::endl;

  auto k = dijkstra_(nodes, nodes[0], nodes[2]);

  for (auto j : k) {
    std::cout << j.x << " " << j.y << " " << j.cost << std::endl;
  }
  //        for(auto n : arr)
  //        {
  //            for(auto k : n.neighbors){
  //                std::cout << n.x << " " << n.y << " " << k.node->x << " " <<
  //                k.node->y << std::endl;
  //            }
  //        }
}

void swerveExtendTest() {
  frc::SwerveDriveKinematics<4> kin = frc::SwerveDriveKinematics<4>(
      frc::Translation2d(0.5_m, 0.5_m), frc::Translation2d(0.5_m, -0.5_m),
      frc::Translation2d(-0.5_m, 0.5_m), frc::Translation2d(-0.5_m, -0.5_m));
  swerve::SwerveState start{{0, 0}, {0, 0},    {0, 0},
                            {0, 0}, {0, 0, 0}, {0, 0, 0}};

  swerve::SwerveState end{{1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1, 1}, {1, 1, 1}};
  swerve::SwerveConfig config{1,         70,         10,        {.1}, {.1},
                              {.1},      {.1},       {.1},      {.1}, {.5, .5},
                              {.5, -.5}, {-.5, -.5}, {-.5, .5}, kin};
  swerve::RRTConfig rrtConfig{1, 100, .1, .1, .1};
  auto k = swerve::extend({start}, {end}, config, rrtConfig);
  std::cout << k.state.position.p.x << " " << k.state.position.p.y << std::endl;
}

int main() {
  swerveExtendTest();

  return 0;
}
