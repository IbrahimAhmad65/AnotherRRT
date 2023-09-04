#include "RRT/RRTPointMass.h"
#include "Debug/Timer.h"

int main() {
    std::vector<Node> path;
    {
        Timer timer;
//        for (int i = 0; i < 100; ++i) {

        RRTPointMassConfig config = RRTPointMassConfig();
        config.maxX = 3;
        config.maxY = 3;
        config.maxAccel = 10;
        config.maxVel = 2;
        config.radiusOfCompletion = .5;
        config.iterations = 5000;
        config.maxTime = 50;
        Node start = {1, 1, 1, -1};
        Node end = {2, 2, 0, -1};
        path = rrtPointMass(start, end, config);
//        std::cout << "Path: " << path.size() << std::endl;
//    printPath(path);
//        }
    }
    printPath(path);
//        path[0] = {0,0,0,0};
    std::cout << "Path: " << path[0].time << std::endl;
    return 0;
}
