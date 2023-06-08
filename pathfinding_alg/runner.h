#pragma once

#include <emscripten.h>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

class PathfindingRunner {
private:
    std::mutex mutex;
public:
    void runAlgorithms(Grid& grid, Node* start, Node* end) {
        std::vector<std::unique_ptr<PathfindingAlgorithm>> algorithms;
        algorithms.push_back(std::make_unique<BFS>());
        algorithms.push_back(std::make_unique<DFS>());
        algorithms.push_back(std::make_unique<Dijkstra>());
        algorithms.push_back(std::make_unique<AStar>());

        std::vector<std::thread> threads;

        for (auto& algorithm : algorithms) {
            threads.push_back(std::thread([algorithm = algorithm.get(), &grid, start, end]() {
                algorithm->setup(grid, start, end);
                while (algorithm->step(grid)) {
                    // To ensure thread safety, we might use a lock here. For example, a mutex.
                    std::lock_guard<std::mutex> lock(mutex);
                    exportStateForVisualization(algorithm->get_visited_nodes(), algorithm->get_path());

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                // After finishing the algorithm's work, save or display the final path.
                // Don't forget to clear the grid or reset its state if necessary.
                }));
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }

    // Declare updateVisualization function to be called from C++
    EM_JS(void, updateVisualization, (const std::vector<int>& visitedNodes, const std::vector<int>& path), {
        // This is JavaScript code
        // Call the updateVisualization function defined in the React component
        window.updateVisualization(visitedNodes, path);
        });

    void exportStateForVisualization(const std::unordered_set<Node*>& visitedNodes, const std::vector<Node*>& path) {
        // Convert visitedNodes and path to arrays of IDs...
        std::vector<int> visitedNodes_ids;
        for (auto& node : visitedNodes) {
            visitedNodes_ids.push_back(node->id);
        }

        std::vector<int> path_ids;
        for (auto& node : path) {
            path_ids.push_back(node->id);
        }

        // Call the JavaScript function
        updateVisualization(visitedNodes_ids, path_ids);
    }

};




//class PathfindingRunner {
//public:
//    template<typename GridType>
//    void runAlgorithms(GridType& grid) {
//        std::vector<std::jthread> threads;
//
//        // Create BFS
//        BFS bfs;
//        bfs.setup(grid, grid.get_start_node(), grid.get_end_node());
//        threads.emplace_back([&]() { bfs.step(grid); });
//
//        // Create DFS
//        DFS dfs;
//        dfs.setup(grid, grid.get_start_node(), grid.get_end_node());
//        threads.emplace_back([&]() { dfs.step(grid); });
//
//        // Create Dijkstra's algorithm
//        Dijkstra dijkstra;
//        dijkstra.setup(grid, grid.get_start_node(), grid.get_end_node());
//        threads.emplace_back([&]() { dijkstra.step(grid); });
//
//        // Create A*
//        AStar aStar;
//        aStar.setup(grid, grid.get_start_node(), grid.get_end_node());
//        threads.emplace_back([&]() { aStar.step(grid); });
//
//        // Wait for all threads to finish
//        for (auto& thread : threads) {
//            if (thread.joinable()) {
//                thread.join();
//            }
//        }
//    }
//};

//class PathfindingRunner {
//public:
//    template<typename GridType, typename AlgorithmType>
//    void runAlgorithm(GridType& grid, AlgorithmType& algorithm) {
//        algorithm.setup(grid, grid.get_start_node(), grid.get_end_node());
//
//        bool running = true;
//        while (running) {
//            running = algorithm.step(grid);
//
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            drawGrid(grid, algorithm.get_path(), algorithm.get_visited_nodes());
//        }
//    }
//
//    void drawGrid(Grid& grid, const std::vector<Node*>& path, const std::unordered_set<Node*>& visited_nodes) {
//        // Clear the console
//        std::cout << "\033[2J\033[1;1H";
//
//        // Draw the grid
//        for (int y = 0; y < grid.get_height(); y++) {
//            for (int x = 0; x < grid.get_width(); x++) {
//                Node* node = grid.get_node(x, y);
//                if (node == grid.get_start_node()) {
//                    std::cout << 'S';
//                }
//                else if (node == grid.get_end_node()) {
//                    std::cout << 'E';
//                }
//                else if (std::find(path.begin(), path.end(), node) != path.end()) {
//                    std::cout << '*';
//                }
//                else if (visited_nodes.find(node) != visited_nodes.end()) {
//                    std::cout << '.';
//                }
//                else if (node->obstacle) {
//                    std::cout << '#';
//                }
//                else {
//                    std::cout << ' ';
//                }
//            }
//            std::cout << '\n';
//        }
//    }
//};
