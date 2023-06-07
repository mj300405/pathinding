#pragma once

#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"


#include <vector>
#include <thread>
#include <memory>
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

#include <vector>
#include <thread>
#include <memory>
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

class PathfindingRunner {
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
                    // Export the current state of the algorithm for visualization.
                    // Note that this would need to be done in a thread-safe manner,
                    // since multiple threads could be trying to export their state at the same time.
                    exportStateForVisualization(algorithm->get_visited_nodes(), algorithm->get_path());

                    // Sleep for a bit to slow down the loop and allow the visualization to update.
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                auto path = algorithm->get_path();  // Save or display the final path
                // Remember to clear the grid or reset its state here if necessary.
                }));
        }

        // Join all threads
        for (auto& thread : threads) {
            thread.join();
        }
    }

    void exportStateForVisualization(const std::unordered_set<Node*>& visitedNodes, const std::vector<Node*>& path) {
        // This function would need to somehow notify the JavaScript environment about the current state
        // of the algorithm, so it can update the visualization. The specific mechanism for doing this will
        // depend on how you're compiling and loading the WebAssembly module.
        //
        // For example, you might do something like this:
        //   EM_ASM({
        //     updateVisualization($0, $1);
        //   }, visitedNodes, path);
        //
        // where updateVisualization is a JavaScript function that updates the visualization based on
        // the current visited nodes and path.
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
