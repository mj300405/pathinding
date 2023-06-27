module;

#include <vector>;
#include <thread>;
#include <unordered_set>;

export module pathfindingrunner;

import astar;
import dijkstra;
import dfs;
import bfs;
import node;
import grid;

export class PathfindingRunner {
    Grid grid;
    Node* start;
    Node* end;

    std::vector<std::unordered_set<Node*>> visited_dfs;
    std::vector<std::unordered_set<Node*>> visited_bfs;
    std::vector<std::unordered_set<Node*>> visited_dijkstra;
    std::vector<std::unordered_set<Node*>> visited_astar;
    std::vector<std::thread> threads;

    AStar astar;
    Dijkstra dijkstra;
    DFS dfs;
    BFS bfs;

public:
    std::vector<int> get_visited_dfs() {
        std::vector<int> result;
        for (const auto& set : visited_dfs) {
            for (const Node* node : set) {
                result.push_back(node->id);
            }
        }
        return result;
    }

    std::vector<int> get_visited_bfs() {
        std::vector<int> result;
        for (const auto& set : visited_bfs) {
            for (const Node* node : set) {
                result.push_back(node->id);
            }
        }
        return result;
    }

    std::vector<int> get_visited_dijkstra() {
        std::vector<int> result;
        for (const auto& set : visited_dijkstra) {
            for (const Node* node : set) {
                result.push_back(node->id);
            }
        }
        return result;
    }

    std::vector<int> get_visited_astar() {
        std::vector<int> result;
        for (const auto& set : visited_astar) {
            for (const Node* node : set) {
                result.push_back(node->id);
            }
        }
        return result;
    }

    std::vector<int> get_path_dfs() {
        std::vector<int> result;
        for (const Node* node : dfs.get_path()) {
            result.push_back(node->id);
        }
        return result;
    }

    std::vector<int> get_path_bfs() {
        std::vector<int> result;
        for (const Node* node : bfs.get_path()) {
            result.push_back(node->id);
        }
        return result;
    }

    std::vector<int> get_path_dijkstra() {
        std::vector<int> result;
        for (const Node* node : dijkstra.get_path()) {
            result.push_back(node->id);
        }
        return result;
    }
    
    std::vector<int> get_path_astar() {
        std::vector<int> result;
        for (const Node* node : astar.get_path()) {
            result.push_back(node->id);
        }
        return result;
    }

    void set_visited_dfs(std::vector<std::unordered_set<Node*>> visited) {
        visited_dfs = visited;
    }

    void set_visited_bfs(std::vector<std::unordered_set<Node*>> visited) {
        visited_bfs = visited;
    }

    void set_visited_dijkstra(std::vector<std::unordered_set<Node*>> visited) {
        visited_dijkstra = visited;
    }

    void set_visited_astar(std::vector<std::unordered_set<Node*>> visited) {
        visited_astar = visited;
    }

    PathfindingRunner(std::vector<int> walls, int width, int height, int startNode, int endNode)
        : grid(width, height) {
        start = grid.get_node(startNode % width, startNode / width);
        end = grid.get_node(endNode % width, endNode / width);
        for (auto wall : walls) {
            grid.get_node(wall % width, wall / width)->obstacle = true;
        };

        Grid grid1 = grid;
        Grid grid2 = grid;
        Grid grid3 = grid;
        Grid grid4 = grid;
        astar.setup(grid1, start, end);
        dijkstra.setup(grid2, start, end);
        bfs.setup(grid3, start, end);
        dfs.setup(grid4, start, end);
    }

    void runAlgorithms() {
        threads.push_back(std::thread([&]() {
            while (astar.step(grid)) {
                visited_astar.push_back(astar.get_visited_nodes());
            }
            }));
        threads.push_back(std::thread([&]() {
            while (dijkstra.step(grid)) {
                visited_dijkstra.push_back(dijkstra.get_visited_nodes());
            }
            }));
        threads.push_back(std::thread([&]() {
            while (bfs.step(grid)) {
                visited_bfs.push_back(bfs.get_visited_nodes());
            }
            }));
        threads.push_back(std::thread([&]() {
            while (dfs.step(grid)) {
                visited_dfs.push_back(dfs.get_visited_nodes());
            }
            }));

        for (auto& thread : threads) {
            thread.join();
        }

        threads.clear();
    }

    AStar& getAstar() { return astar; }
    Dijkstra& getDijkstra() { return dijkstra; }
    DFS& getDFS() { return dfs; }
    BFS& getBFS() { return bfs; }
};


EMSCRIPTEN_BINDINGS(stl_wrappers) {
    emscripten::register_vector<int>("VectorInt");
    emscripten::register_vector<std::vecotr<int>>("VectorVectorInt");
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
        ;
}