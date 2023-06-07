#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

#include "node.h"

//class DFS : public PathfindingAlgorithm {
//private:
//    Node* start;
//    Node* end;
//    std::unordered_map<Node*, Node*> came_from;
//    std::unordered_set<Node*> visited_nodes;
//    std::stack<Node*> open_set;
//    std::vector<Node*> path;
//
//public:
//    void setup(Grid& grid, Node* start, Node* end) override {
//        this->start = start;
//        this->end = end;
//        came_from.clear();
//        visited_nodes.clear();
//        while (!open_set.empty())
//            open_set.pop();
//        path.clear();
//
//        open_set.push(start);
//    }
//
//    bool step(Grid& grid) override {
//        if (open_set.empty()) {
//            if (path.empty() && came_from.count(end)) {
//                Node* current = end;
//                while (current) {
//                    path.push_back(current);
//                    current = came_from[current];
//                }
//                std::reverse(path.begin(), path.end());
//            }
//            return false;
//        }
//
//        Node* current = open_set.top();
//        open_set.pop();
//
//        if (current == end) {
//            return false;
//        }
//
//        for (auto neighbor : grid.get_neighbors(current)) {
//            if (visited_nodes.count(neighbor) || neighbor->obstacle)
//                continue;
//
//            came_from[neighbor] = current;
//            open_set.push(neighbor);
//            visited_nodes.insert(neighbor);
//        }
//
//        return true;
//    }
//
//    std::vector<Node*> get_path() override {
//        return path;
//    }
//
//    std::unordered_set<Node*> get_visited_nodes() override {
//        return visited_nodes;
//    }
//};


class DFS : public PathfindingAlgorithm {
private:
    Node* start;
    Node* end;
    std::unordered_map<Node*, Node*> came_from;
    std::unordered_set<Node*> visited_nodes;
    std::stack<Node*> open_set;
    std::vector<Node*> path;
    bool is_path_found = false;

public:
    void setup(Grid& grid, Node* start, Node* end) override {
        this->start = start;
        this->end = end;
        came_from.clear();
        visited_nodes.clear();
        while (!open_set.empty())
            open_set.pop();
        path.clear();
        is_path_found = false;

        open_set.push(start);
        visited_nodes.insert(start);
    }

    bool step(Grid& grid) override {
        if (is_path_found || open_set.empty()) {
            return false;
        }

        Node* current = open_set.top();
        open_set.pop();

        for (auto neighbor : grid.get_neighbors(current)) {
            if (visited_nodes.count(neighbor) || neighbor->obstacle)
                continue;

            came_from[neighbor] = current;
            open_set.push(neighbor);
            visited_nodes.insert(neighbor);

            if (neighbor == end) {
                is_path_found = true;
                Node* path_current = end;
                while (path_current) {
                    path.push_back(path_current);
                    path_current = came_from[path_current];
                }
                std::reverse(path.begin(), path.end());
                return false;
            }
        }

        return true;
    }

    std::vector<Node*> get_path() override {
        return path;
    }

    std::unordered_set<Node*> get_visited_nodes() override {
        return visited_nodes;
    }
};
