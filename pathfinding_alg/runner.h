#pragma once

#include <vector>
#include <thread>
#include "astar.h"
#include "dijkstra.h"
#include "dfs.h"
#include "bfs.h"
#include "node.h"
#include <unordered_set>
#include <emscripten/bind.h>

class PathfindingRunner {
    Grid grid;
    Node* start;
    Node* end;

    std::vector<std::unordered_set<Node*>> visited_dfs;
    std::vector<std::unordered_set<Node*>> visited_bfs;
    std::vector<std::unordered_set<Node*>> visited_dijkstra;
    std::vector<std::unordered_set<Node*>> visited_astar;
    std::vector<std::thread> threads;
    
public:
    Grid grid_dfs = Grid(30,30);
    Grid grid_bfs = Grid(30,30);
    Grid grid_dijkstra = Grid(30,30);
    Grid grid_astar = Grid(30,30);

    AStar astar;
    Dijkstra dijkstra;
    DFS dfs;
    BFS bfs;

    std::vector<std::vector<int>> get_visited_dfs();
    std::vector<std::vector<int>> get_visited_bfs();
    std::vector<std::vector<int>> get_visited_dijkstra();
    std::vector<std::vector<int>> get_visited_astar();

    int size_of_1d_vector(std::vector<int> vec);
    int size_of_2d_vector(std::vector<std::vector<int>> vec);

    void set_visited_dfs(std::vector<std::unordered_set<Node*>> visited);
    void set_visited_bfs(std::vector<std::unordered_set<Node*>> visited);
    void set_visited_dijkstra(std::vector<std::unordered_set<Node*>> visited);
    void set_visited_astar(std::vector<std::unordered_set<Node*>> visited);

    std::vector<int> get_path_dfs();
    std::vector<int> get_path_bfs();
    std::vector<int> get_path_dijkstra();
    std::vector<int> get_path_astar();
    
    PathfindingRunner(std::vector<int> walls, int width, int height, int startNode, int endNode);
    
    void runAlgorithms();

    AStar& getAstar() { return astar; }
    Dijkstra& getDijkstra() { return dijkstra; }
    DFS& getDFS() { return dfs; }
    BFS& getBFS() { return bfs; }
};


EMSCRIPTEN_BINDINGS(stl_wrappers) {
    emscripten::register_vector<int>("VectorInt");
    emscripten::register_vector<std::vector<int>>("VectorVectorInt");
}

EMSCRIPTEN_BINDINGS(PathfindingRunner) {
    emscripten::class_<PathfindingRunner>("PathfindingRunner")
        .constructor<std::vector<int>, int, int, int, int>()
        .function("runAlgorithms", &PathfindingRunner::runAlgorithms)
        .function("get_visited_dfs", &PathfindingRunner::get_visited_dfs)
        .function("set_visited_dfs", &PathfindingRunner::set_visited_dfs)
        .function("get_visited_bfs", &PathfindingRunner::get_visited_bfs)
        .function("set_visited_bfs", &PathfindingRunner::set_visited_bfs)
        .function("get_visited_dijkstra", &PathfindingRunner::get_visited_dijkstra)
        .function("set_visited_dijkstra", &PathfindingRunner::set_visited_dijkstra)
        .function("get_visited_astar", &PathfindingRunner::get_visited_astar)
        .function("set_visited_astar", &PathfindingRunner::set_visited_astar)
        .function("get_path_dfs", &PathfindingRunner::get_path_dfs)
		.function("get_path_bfs", &PathfindingRunner::get_path_bfs)
        .function("get_path_dijkstra", &PathfindingRunner::get_path_dijkstra)
		.function("get_path_astar", &PathfindingRunner::get_path_astar)
        .function("size_of_1d_vector", &PathfindingRunner::size_of_1d_vector)
        .function("size_of_2d_vector", &PathfindingRunner::size_of_2d_vector)
        ;
}