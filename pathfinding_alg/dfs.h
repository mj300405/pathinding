#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <compare>

#include "node.h"


class DFS : public PathfindingAlgorithm {
private:
    std::unordered_map<Node*, Node*> came_from;

public:
    std::vector<Node*> find_path(Grid& grid, Node* start, Node* end) {
        std::vector<Node*> path;

        std::vector<Node*> stack;
        stack.push_back(start);

        // A set of visited nodes
        std::unordered_set<Node*> visited;

        while (!stack.empty()) {
            Node* current = stack.back();
            stack.pop_back();

            // If we've reached the goal, we're done
            if (current == end) {
                // Reconstruct the path from the end node to the start node
                path.push_back(current);
                while (current != start) {
                    current = came_from[current];
                    path.push_back(current);
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            // If we've already visited this node, skip it
            if (visited.find(current) != visited.end() || current->obstacle) {
                continue;
            }

            visited.insert(current);

            // Add neighbors to the stack
            for (Node* neighbor : grid.get_neighbors(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    stack.push_back(neighbor);
                    came_from[neighbor] = current;
                }
            }
        }

        // If no path was found, return an empty path
        return path;
    }
};

