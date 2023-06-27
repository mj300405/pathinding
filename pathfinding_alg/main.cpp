//#include <emscripten/bind.h>
#include "runner.h"
#include "helper.h"
#include "bfs.h"
#include "dfs.h"
#include "dijkstra.h"
#include "astar.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_set>
//using namespace emscripten;

//PathfindingRunner* createRunner(std::vector<int> gridArray, int width, int height, int startNode, int endNode) {
//    return new PathfindingRunner(gridArray, width, height, startNode, endNode);
//}
//
//void runAlgorithms(PathfindingRunner* runner) {
//    runner->runAlgorithms();
//}
//
//EMSCRIPTEN_BINDINGS(my_module) {
//    function("createRunner", &createRunner, allow_raw_pointers());
//    function("runAlgorithms", &runAlgorithms, allow_raw_pointers());
//
//    register_vector<int>("VectorInt");
//}


//int main() {
//    const int gridWidth = 10;
//    const int gridHeight = 10;
//    Grid grid(gridWidth, gridHeight, 0, 0, 0, 9);
//
//    // Add some obstacles for the algorithm to avoid
//    grid.get_node(3, 3)->make_obstacle();
//    grid.get_node(3, 4)->make_obstacle();
//    grid.get_node(3, 5)->make_obstacle();
//    grid.get_node(3, 6)->make_obstacle();
//
//    PathfindingRunner runner({33,34,35,36}, 10, 10, 0, 9);
//    runner.runAlgorithms();
//
//    AStar dfs;
//    dfs.setup(grid, grid.get_start_node(), grid.get_end_node());
//
//    bool running = true;
//    while (running) {
//        running = dfs.step(grid);
//
//        // Clear the console
//        std::cout << "\033[2J\033[1;1H";
//
//        // Get the current path
//        std::vector<Node*> path = dfs.get_path();
//
//        // Get the visited nodes
//        std::unordered_set<Node*> visited_nodes = dfs.get_visited_nodes();
//
//        // Draw the grid
//        for (int x = 0; x < grid.get_width(); x++) {
//            for (int y = 0; y < grid.get_height(); y++) {
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
//
//        // Sleep for a bit to slow down the loop
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//
//    // Clear the console one more time before drawing the final path
//    std::cout << "\033[2J\033[1;1H";
//
//    // Get the final path
//    std::vector<Node*> final_path = dfs.get_path();
//
//    // Draw the final grid with the path
//    for (int x = 0; x < grid.get_width(); x++) {
//        for (int y = 0; y < grid.get_height(); y++) {
//            Node* node = grid.get_node(x, y);
//            if (node == grid.get_start_node()) {
//                std::cout << 'S';
//            }
//            else if (node == grid.get_end_node()) {
//                std::cout << 'E';
//            }
//            else if (std::find(final_path.begin(), final_path.end(), node) != final_path.end()) {
//                std::cout << '*';
//            }
//            else if (node->obstacle) {
//                std::cout << '#';
//            }
//            else {
//                std::cout << ' ';
//            }
//        }
//        std::cout << '\n';
//    }
//
//    // Pause the program
//    std::cout << "Press enter to continue...";
//    std::cin.get();
//
//    return 0;
//}

int main() {
    const int gridWidth = 10;
    const int gridHeight = 10;

    std::vector<int> obstacles = { 33, 34, 35, 36 };
    int startNode = 0;
    int endNode = 9;

    // Initialize the runner with the grid size, obstacles, and start/end nodes
    PathfindingRunner runner(obstacles, gridWidth, gridHeight, startNode, endNode);

    // Run the algorithms
    runner.runAlgorithms();

    // Get the final path
    std::vector<int> final_path = runner.get_path_dfs();

    DFS& dfs = runner.getDFS();  // Get the DFS object from runner
    Grid& grid = runner.grid_dfs;  // Get the grid from the DFS object

    // Draw the final grid with the path
    for (int x = 0; x < grid.get_width(); x++) {
        for (int y = 0; y < grid.get_height(); y++) {
            Node* node = grid.get_node(x, y);
            if (node == grid.get_start_node()) {
                std::cout << 'S';
            }
            else if (node == grid.get_end_node()) {
                std::cout << 'E';
            }
            else if (node->obstacle) {
                std::cout << '#';
            }
            else if (std::find(final_path.begin(), final_path.end(), node->id) != final_path.end()) {
                std::cout << '*';
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}