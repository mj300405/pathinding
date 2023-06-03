#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <stop_token>

#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"


#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <vector>
#include <optional>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <vector>
#include <optional>

class MultiPathfinder {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::unordered_map<std::string, std::vector<Node*>> paths;

public:
    void runAStar(Grid& grid, Node* start, Node* end) {
        AStar astar;
        auto path = astar.find_path(grid, start, end);
        {
            std::lock_guard<std::mutex> lock(mtx);
            paths["AStar"] = path;
        }
        cv.notify_one();
    }

    void runDijkstra(Grid& grid, Node* start, Node* end) {
        Dijkstra dijkstra;
        auto path = dijkstra.find_path(grid, start, end);
        {
            std::lock_guard<std::mutex> lock(mtx);
            paths["Dijkstra"] = path;
        }
        cv.notify_one();
    }

    void runBFS(Grid& grid, Node* start, Node* end) {
        BFS bfs;
        auto path = bfs.find_path(grid, start, end);
        {
            std::lock_guard<std::mutex> lock(mtx);
            paths["BFS"] = path;
        }
        cv.notify_one();
    }

    void runDFS(Grid& grid, Node* start, Node* end) {
        DFS dfs;
        auto path = dfs.find_path(grid, start, end);
        {
            std::lock_guard<std::mutex> lock(mtx);
            paths["DFS"] = path;
        }
        cv.notify_one();
    }

    std::unordered_map<std::string, std::vector<Node*>> runAll(Grid& grid, Node* start, Node* end) {
        std::thread t1(&MultiPathfinder::runAStar, this, std::ref(grid), start, end);
        std::thread t2(&MultiPathfinder::runDijkstra, this, std::ref(grid), start, end);
        std::thread t3(&MultiPathfinder::runBFS, this, std::ref(grid), start, end);
        std::thread t4(&MultiPathfinder::runDFS, this, std::ref(grid), start, end);
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return paths.size() == 4; });
        }
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        return paths;
    }
};

