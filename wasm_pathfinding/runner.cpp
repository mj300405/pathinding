#include "runner.h"

PathfindingRunner::PathfindingRunner(std::vector<int>& gridArray, int width, int height, int startNode, int endNode)
    : grid(width, height) {
    start = grid.get_node(startNode % width, startNode / width);
    end = grid.get_node(endNode % width, endNode / width);

    astar.setup(grid, start, end);
    dijkstra.setup(grid, start, end);
    bfs.setup(grid, start, end);
    dfs.setup(grid, start, end);
}

void PathfindingRunner::runAlgorithms() {
    threads.push_back(std::thread([&]() { while (astar.step(grid)); }));
    threads.push_back(std::thread([&]() { while (dijkstra.step(grid)); }));
    threads.push_back(std::thread([&]() { while (bfs.step(grid)); }));
    threads.push_back(std::thread([&]() { while (dfs.step(grid)); }));

    for (auto& thread : threads) {
        thread.join();
    }

    threads.clear();
}
