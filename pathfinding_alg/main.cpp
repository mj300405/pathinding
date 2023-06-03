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
    Grid grid(10, 10);
    Node* start = grid.get_node(0, 0);
    Node* end = grid.get_node(9, 9);
    MultiPathfinder pathfinder;
    auto paths = pathfinder.runAll(grid, start, end);

    // For each algorithm and its path
    for (const auto& [algorithm, path] : paths) {
        std::cout << "Path found by " << algorithm << ":\n";
        for (const auto& node : path) {
            std::cout << "(" << node->x << ", " << node->y << ") ";
        }
        std::cout << '\n';
    }


    return 0;
}
