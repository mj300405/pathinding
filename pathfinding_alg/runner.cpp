#include "runner.h"
#include "helper.h"
#include <set>
// #include <emscripten.h>

PathfindingRunner::PathfindingRunner(std::vector<int> walls, int width, int height, int startNode, int endNode)
    : grid(width, height) {
    start = grid.get_node(startNode % width, startNode / width);
    end = grid.get_node(endNode % width, endNode / width);

    std::cout << "START: " << startNode << std::endl;
    std::cout << "END: " << endNode << std::endl;
    
    for(auto wall : walls) {
		grid.get_node(wall % width, wall / width)->obstacle = true;
    };

    grid_dfs = grid;
    grid_bfs = grid;
    grid_dijkstra = grid;
    grid_astar = grid;
    
    // astar.setup(grid_astar, start, end);
    // dijkstra.setup(grid_dijkstra, start, end);
    // bfs.setup(grid_bfs, start, end);


    dfs.setup(grid_dfs, grid_dfs.get_node(startNode % width, startNode / width),  grid_dfs.get_node(endNode % width, endNode / width));

    astar.setup(grid_astar, grid_astar.get_node(startNode % width, startNode / width),  grid_astar.get_node(endNode % width, endNode / width));

    bfs.setup(grid_bfs, grid_bfs.get_node(startNode % width, startNode / width),  grid_bfs.get_node(endNode % width, endNode / width));

    dijkstra.setup(grid_dijkstra, grid_dijkstra.get_node(startNode % width, startNode / width),  grid_dijkstra.get_node(endNode % width, endNode / width));
}

//void PathfindingRunner::runAlgorithms() {
//    threads.push_back(std::thread([&]() { 
//        while (astar.step(grid)) {
//            visited_astar.push_back(astar.get_visited_nodes());
//        }
//    }));
//    threads.push_back(std::thread([&]() {
//        while (dijkstra.step(grid)) {
//            visited_dijkstra.push_back(dijkstra.get_visited_nodes());
//        }
//    }));
//    threads.push_back(std::thread([&]() {
//        while (bfs.step(grid)) {
//            visited_bfs.push_back(bfs.get_visited_nodes());
//        }
//    }));
//    threads.push_back(std::thread([&]() {
//        while (dfs.step(grid)) {
//            visited_dfs.push_back(dfs.get_visited_nodes());
//        }
//    }));
//
//    for (auto& thread : threads) {
//        thread.join();
//    }
//
//    threads.clear();
//}

void PathfindingRunner::runAlgorithms() {
    while (astar.step(grid_astar)) {
        visited_astar.push_back(astar.get_visited_nodes());
    }

    while (dijkstra.step(grid_dijkstra)) {
        visited_dijkstra.push_back(dijkstra.get_visited_nodes());
    }

    while (bfs.step(grid_bfs)) {
        visited_bfs.push_back(bfs.get_visited_nodes());
    }

    while (dfs.step(grid_dfs)) {
        visited_dfs.push_back(dfs.get_visited_nodes());
    }
}


std::vector<std::vector<int>> PathfindingRunner::get_visited_dfs() {
    std::vector<std::vector<int>> result;
    std::set<int> numbers;
    for (const auto& set : visited_dfs) {
        std::vector<int> vec;
        for (const Node* node : set) {
            if(numbers.contains(node->id)) continue;
            numbers.insert(node->id);
            vec.push_back(node->id);
        }
        result.push_back(vec);
    }
    return result;
}


std::vector<std::vector<int>> PathfindingRunner::get_visited_bfs() {
    std::vector<std::vector<int>> result;
    std::set<int> numbers;

    for (const auto& set : visited_bfs) {
        std::vector<int> vec;
        for (const Node* node : set) {
            if(numbers.contains(node->id)) continue;
            numbers.insert(node->id);
            vec.push_back(node->id);
        }
        result.push_back(vec);
    }
    return result;
}


std::vector<std::vector<int>> PathfindingRunner::get_visited_dijkstra() {
    std::vector<std::vector<int>> result;
    std::set<int> numbers;

    for (const auto& set : visited_dijkstra) {
        std::vector<int> vec;
        for (const Node* node : set) {
            if(numbers.contains(node->id)) continue;
            numbers.insert(node->id);
            vec.push_back(node->id);
        }
        result.push_back(vec);
    }
    return result;
}


std::vector<std::vector<int>> PathfindingRunner::get_visited_astar(){
    std::vector<std::vector<int>> result;
    std::set<int> numbers;
    for (const auto& set : visited_astar) {
        std::vector<int> vec;
        for (const Node* node : set) {
            if(numbers.contains(node->id)) continue;
            numbers.insert(node->id);
            vec.push_back(node->id);
        }
        result.push_back(vec);
    }
    return result;
}


std::vector<int> PathfindingRunner::get_path_dfs() {
	std::vector<int> result;
    for (const Node* node : dfs.get_path()) {
        result.push_back(node->id);
        //emscripten_log(EM_LOG_CONSOLE, "NODE_ID: %d", node->id);
    }
	return result;
}

std::vector<int> PathfindingRunner::get_path_bfs() {
	std::vector<int> result;
	for (const Node* node : bfs.get_path()) {
		result.push_back(node->id);
	}
	return result;
}

std::vector<int> PathfindingRunner::get_path_dijkstra() {
	std::vector<int> result;
	for (const Node* node : dijkstra.get_path()) {
		result.push_back(node->id);
	}
	return result;
}

std::vector<int> PathfindingRunner::get_path_astar() {
	std::vector<int> result;
	for (const Node* node : astar.get_path()) {
		result.push_back(node->id);
	}
	return result;
}

int PathfindingRunner::size_of_2d_vector(std::vector<std::vector<int>> vec){
    return vec.size();
}

int PathfindingRunner::size_of_1d_vector(std::vector<int> vec) {
    return vec.size();
}
//std::vector<std::vector<int>> PathfindingRunner::get_visited_dfs() {
//    std::vector<std::vector<int>> result;
//    for (const auto& set : visited_dfs) {
//        std::vector<int> vec;
//        for (const Node* node : set) {
//            vec.push_back(node->id);
//        }
//        result.push_back(vec);
//    }
//    return result;
//}
//
//
//std::vector<std::vector<int>> PathfindingRunner::get_visited_bfs(){
//    std::vector<std::vector<int>> result;
//    for (const auto& set : visited_bfs) {
//        std::vector<int> vec;
//        for (const Node* node : set) {
//            vec.push_back(node->id);
//        }
//        result.push_back(vec);
//    }
//    return result;
//}
//
//std::vector<std::vector<int>> PathfindingRunner::get_visited_dijkstra(){
//    std::vector<std::vector<int>> result;
//    for (const auto& set : visited_dijkstra) {
//        std::vector<int> vec;
//        for (const Node* node : set) {
//            vec.push_back(node->id);
//        }
//        result.push_back(vec);
//    }
//    return result;
//}
//
//std::vector<std::vector<int>> PathfindingRunner::get_visited_astar(){
//    std::vector<std::vector<int>> result;
//    for (const auto& set : visited_astar) {
//        std::vector<int> vec;
//        for (const Node* node : set) {
//            vec.push_back(node->id);
//        }
//        result.push_back(vec);
//    }
//    return result;
//}

void PathfindingRunner::set_visited_dfs(std::vector<std::unordered_set<Node*>> visited){
	visited_dfs = visited;
}

void PathfindingRunner::set_visited_bfs(std::vector<std::unordered_set<Node*>> visited){
	visited_bfs = visited;
}

void PathfindingRunner::set_visited_dijkstra(std::vector<std::unordered_set<Node*>> visited){
	visited_dijkstra = visited;
}

void PathfindingRunner::set_visited_astar(std::vector<std::unordered_set<Node*>> visited){
	visited_astar = visited;
}