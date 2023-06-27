//#pragma once
//
//#include <emscripten.h>
//#include <vector>
//#include <thread>
//#include <memory>
//#include <mutex>
//#include "astar.h"
//#include "dijkstra.h"
//#include "dfs.h"
//#include "bfs.h"
//
//
//// Outside the class
//EM_JS(void, updateVisualization, (const std::vector<int>& visitedNodes, const std::vector<int>& path), {
//    // This is JavaScript code
//    // Call the updateVisualization function defined in the React component
//    window.updateVisualization(visitedNodes, path);
//    });
//
//
//class PathfindingRunner {
//private:
//    std::mutex mutex;
//    void updateVisualization(const std::vector<int>& visitedNodes, const std::vector<int>& path);
//public:
//    void runAlgorithms(Grid& grid, Node* start, Node* end) {
//        std::vector<std::unique_ptr<PathfindingAlgorithm>> algorithms;
//        algorithms.push_back(std::make_unique<BFS>());
//        algorithms.push_back(std::make_unique<DFS>());
//        algorithms.push_back(std::make_unique<Dijkstra>());
//        algorithms.push_back(std::make_unique<AStar>());
//
//        std::vector<std::thread> threads;
//
//        for (auto& algorithm : algorithms) {
//            threads.push_back(std::thread([this, algorithm = algorithm.get(), &grid, start, end]() {
//                
//                algorithm->setup(grid, start, end);
//                while (algorithm->step(grid)) {
//                    // To ensure thread safety, we might use a lock here. For example, a mutex.
//                    std::lock_guard<std::mutex> lock(mutex);
//                    exportStateForVisualization(algorithm->get_visited_nodes(), algorithm->get_path());
//
//                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//                }
//                // After finishing the algorithm's work, save or display the final path.
//                // Don't forget to clear the grid or reset its state if necessary.
//                }));
//        }
//
//        for (auto& thread : threads) {
//            thread.join();
//        }
//    }
//
//    void exportStateForVisualization(const std::unordered_set<Node*>& visitedNodes, const std::vector<Node*>& path) {
//        // Convert visitedNodes and path to arrays of IDs...
//        std::vector<int> visitedNodes_ids;
//        for (auto& node : visitedNodes) {
//            visitedNodes_ids.push_back(node->id);
//        }
//
//        std::vector<int> path_ids;
//        for (auto& node : path) {
//            path_ids.push_back(node->id);
//        }
//
//        // Call the JavaScript function
//        updateVisualization(visitedNodes_ids, path_ids);
//    }
//
//};


#pragma once

#include <vector>
#include <thread>
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"
#include "node.h"

class PathfindingRunner {
    Grid grid;
    Node* start;
    Node* end;

    std::vector<std::thread> threads;

    AStar astar;
    Dijkstra dijkstra;
    DFS dfs;
    BFS bfs;

public:
    PathfindingRunner(std::vector<int>& gridArray, int width, int height, int startNode, int endNode);
    void runAlgorithms();

    AStar& getAstar() { return astar; }
    Dijkstra& getDijkstra() { return dijkstra; }
    DFS& getDFS() { return dfs; }
    BFS& getBFS() { return bfs; }
};