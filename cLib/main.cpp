#include "RRT/RRTPointMass.h"
#include "Debug/Timer.h"

int main() {
    {
        Timer timer;
//        for (int i = 0; i < 10; ++i) {

        RRTPointMassConfig config = RRTPointMassConfig();
        config.maxX = 3;
        config.maxY = 3;
        config.maxAccel = 10;
        config.maxVel = 1;
        config.radiusOfCompletion = .1;
        config.iterations = 5000;
        config.maxTime = 50;
        Node start = {1, 1, 1, -1};
        Node end = {2, 2, 0, -1};
        std::vector<Node> path = rrtPointMass(start, end, config);
//        path[0] = {0,0,0,0};
//    std::cout << "Path: "<< path.size() << std::endl;
//    printPath(path);
//        }
    }
    return 0;
}
