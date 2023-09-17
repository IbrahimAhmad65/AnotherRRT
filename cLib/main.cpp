#include "RRT/RRTPointMass.h"
#include "Debug/Timer.h"
#include "RRT/Djikstra/Graph.h"
#include "RRT/Djikstra/Djikstra.h"
int main() {
    if(false)
    {
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
    }
    else {
        Graph g = Graph();
        GraphNode n1 = {0,0,0,0,1e308,std::vector<Edge>()};
        GraphNode n2 = {1,0,3,2,1e308,std::vector<Edge>()};
        GraphNode n3 = {1,5,6,2,1e308,std::vector<Edge>()};
        g.nodes.push_back(n1);
        g.nodes.push_back(n2);
        g.nodes.push_back(n3);
        auto nodes= generateFilledNodes(g.nodes,1);
//        g.nodes[0].neighbors.erase(g.nodes[0].neighbors.begin());
//        std::cout << "Hey" << std::endl;

        auto k = djikstra_(nodes, nodes[0], nodes[2]);

        for (auto j:k) {
            std::cout << j.x << " " << j.y << " " << j.cost << std::endl;
        }
//        for(auto n : arr)
//        {
//            for(auto k : n.neighbors){
//                std::cout << n.x << " " << n.y << " " << k.node->x << " " << k.node->y << std::endl;
//            }
//        }
    }

    return 0;
}
