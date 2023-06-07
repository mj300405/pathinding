#include<iostream>
#include<thread>
#include<mutex>
#include <chrono>
#include <thread>

#include "node.h"
#include "runner.h"
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"

int main() {
    const int gridWidth = 10;
    const int gridHeight = 10;
    Grid grid(gridWidth, gridHeight, 0, 0, 9, 9);

    // Add some obstacles for the algorithm to avoid
    grid.get_node(3, 3)->make_obstacle();
    grid.get_node(3, 4)->make_obstacle();
    grid.get_node(3, 5)->make_obstacle();
    grid.get_node(3, 6)->make_obstacle();

    BFS dfs;
    dfs.setup(grid, grid.get_start_node(), grid.get_end_node());

    bool running = true;
    while (running) {
        running = dfs.step(grid);

        // Clear the console
        std::cout << "\033[2J\033[1;1H";

        // Get the current path
        std::vector<Node*> path = dfs.get_path();

        // Get the visited nodes
        std::unordered_set<Node*> visited_nodes = dfs.get_visited_nodes();

        // Draw the grid
        for (int y = 0; y < grid.get_height(); y++) {
            for (int x = 0; x < grid.get_width(); x++) {
                Node* node = grid.get_node(x, y);
                if (node == grid.get_start_node()) {
                    std::cout << 'S';
                }
                else if (node == grid.get_end_node()) {
                    std::cout << 'E';
                }
                else if (std::find(path.begin(), path.end(), node) != path.end()) {
                    std::cout << '*';
                }
                else if (visited_nodes.find(node) != visited_nodes.end()) {
                    std::cout << '.';
                }
                else if (node->obstacle) {
                    std::cout << '#';
                }
                else {
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }

        // Sleep for a bit to slow down the loop
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Clear the console one more time before drawing the final path
    std::cout << "\033[2J\033[1;1H";

    // Get the final path
    std::vector<Node*> final_path = dfs.get_path();

    // Draw the final grid with the path
    for (int y = 0; y < grid.get_height(); y++) {
        for (int x = 0; x < grid.get_width(); x++) {
            Node* node = grid.get_node(x, y);
            if (node == grid.get_start_node()) {
                std::cout << 'S';
            }
            else if (node == grid.get_end_node()) {
                std::cout << 'E';
            }
            else if (std::find(final_path.begin(), final_path.end(), node) != final_path.end()) {
                std::cout << '*';
            }
            else if (node->obstacle) {
                std::cout << '#';
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    // Pause the program
    std::cout << "Press enter to continue...";
    std::cin.get();

    return 0;
}


//int main() {
//    const int gridWidth = 10;
//    const int gridHeight = 10;
//    Grid grid(gridWidth, gridHeight, 0, 0, gridWidth - 1, gridHeight - 1);
//
//    // Add some obstacles for the algorithm to avoid
//    grid.get_node(3, 3)->make_obstacle();
//    grid.get_node(3, 4)->make_obstacle();
//    grid.get_node(3, 5)->make_obstacle();
//    grid.get_node(3, 6)->make_obstacle();
//
//    PathfindingRunner runner;
//
//    // Run and visualize BFS
//    std::cout << "Running BFS...\n";
//    BFS bfs;
//    runner.runAlgorithm(grid, bfs);
//
//    // Run and visualize DFS
//    std::cout << "Running DFS...\n";
//    DFS dfs;
//    runner.runAlgorithm(grid, dfs);
//
//    // Run and visualize Dijkstra's algorithm
//    std::cout << "Running Dijkstra's algorithm...\n";
//    Dijkstra dijkstra;
//    runner.runAlgorithm(grid, dijkstra);
//
//    // Run and visualize A*
//    std::cout << "Running A*...\n";
//    AStar aStar;
//    runner.runAlgorithm(grid, aStar);
//
//    return 0;
//}
