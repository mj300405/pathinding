#include<iostream>
#include<thread>
#include<mutex>

#include "node.h"
#include "runner.h"
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

int main() {
    int width = 10;
    int height = 10;
    int startX = 0;
    int startY = 0;
    int endX = 9;
    int endY = 9;

    PathfindingRunner runner(width, height, startX, startY, endX, endY);
    runner.run();

    // Print the paths found by the algorithms
    auto paths = runner.get_paths();
    for (const auto& path : paths) {
        for (const auto& node : path) {
            std::cout << "(" << node->x << ", " << node->y << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}



// TODO make multithread running