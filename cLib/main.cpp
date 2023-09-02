#include <iostream>
#include "RRT/RRTPointMass.h"
int main() {
    RRTPointMassConfig config = RRTPointMassConfig();
    config.maxX = 3;
    config.maxY = 3;
    config.maxAccel = 10;
    config.maxVel = 1;
    config.radiusOfCompletion = 1;
    config.iterations = 50000;
    Node start = {1, 1, 1, -1};
    Node end = {2, 2, 0, -1};
    std::vector<Node> path = rrtPointMass(start, end, config);
    return 0;
}
