#pragma once

#include <compare>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include "node.h"

class AStar : public PathfindingAlgorithm {
private:
    // Keep track of the parent node for each node
    std::unordered_map<Node*, Node*> came_from;

public:
    // Find a path from start to end in the given grid
    std::vector<Node*> find_path(Grid& grid, Node* start, Node* end) {
        std::vector<Node*> path;

        // Initialize the open and closed sets
        std::vector<Node*> open_set;
        open_set.push_back(start);

        std::vector<Node*> closed_set;

        // Keep track of the cost of getting to each node
        std::unordered_map<Node*, int> g_score;
        g_score[start] = 0;

        // Keep track of the estimated cost of getting from each node to the end
        std::unordered_map<Node*, int> f_score;
        f_score[start] = start->heuristic(end);

        // Loop until the open set is empty (i.e., we've searched all reachable nodes)
        while (!open_set.empty()) {
            // Find the node in the open set with the lowest f-score
            auto current = *std::min_element(open_set.begin(), open_set.end(), [&](Node* a, Node* b) {
                return f_score[a] < f_score[b];
                });

            // If we've reached the goal, we're done
            if (current == end) {
                // Reconstruct the path from the end node to the start node
                path.push_back(current);
                while (current != start) {
                    current = came_from[current];
                    path.push_back(current);
                }
                std::reverse(path.begin(), path.end());
                break;
            }

            // Remove the current node from the open set
            open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());

            // Add the current node to the closed set
            closed_set.push_back(current);

            // Explore the neighbors of the current node
            for (auto neighbor : grid.get_neighbors(current)) {
                // If the neighbor is already in the closed set, or it is an obstacle, skip it
                if (std::find(closed_set.begin(), closed_set.end(), neighbor) != closed_set.end() || neighbor->obstacle) {
                    continue;
                }

                // Compute the tentative g-score for this neighbor
                int tentative_g_score = g_score[current] + 1;

                // If the neighbor is not in the open set, add it
                if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end()) {
                    open_set.push_back(neighbor);
                }
                // If the tentative g-score is higher than the current g-score for the neighbor, skip it
                else if (tentative_g_score >= g_score[neighbor]) {
                    continue;
                }

                // We've found a better path to the neighbor, so update its g-score and f-score
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = tentative_g_score + neighbor->heuristic(end);
            }
        }

        return path;
    }
};