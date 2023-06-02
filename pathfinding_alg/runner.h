#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <stop_token>

#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"


class PathfindingRunner {
public:
    PathfindingRunner(int width, int height, int startX, int startY, int endX, int endY)
        : m_width(width), m_height(height), m_startX(startX), m_startY(startY), m_endX(endX), m_endY(endY) {}

    void run() {
        // Declare instances of your pathfinding algorithms
        Dijkstra dijkstra;
        AStar astar;
        BFS bfs;
        DFS dfs;

        // Create jthreads to run each algorithm
        std::jthread t1(&PathfindingRunner::find_path, std::ref(dijkstra));
        std::jthread t2(&PathfindingRunner::find_path, std::ref(astar));
        std::jthread t3(&PathfindingRunner::find_path, std::ref(bfs));
        std::jthread t4(&PathfindingRunner::find_path, std::ref(dfs));

        // No need to manually join jthreads; they automatically join on destruction
    }

    std::vector<std::vector<Node*>> get_paths() const {
        return m_paths;
    }

private:
    void find_path(std::stop_token stop_token, PathfindingAlgorithm& algorithm) {
        // Each thread creates its own grid and start/end nodes
        Grid grid(m_width, m_height);
        Node* start = grid.get_node(m_startX, m_startY);
        Node* end = grid.get_node(m_endX, m_endY);

        std::vector<Node*> path = algorithm.find_path(grid, start, end);

        // If the stop_token is signaled, return early
        if (stop_token.stop_requested()) {
            return;
        }

        // Add the path to the list of paths
        std::lock_guard<std::mutex> lock(m_mutex);
        m_paths.push_back(path);
    }

    int m_width, m_height;
    int m_startX, m_startY;
    int m_endX, m_endY;
    std::vector<std::vector<Node*>> m_paths;
    std::mutex m_mutex;
};