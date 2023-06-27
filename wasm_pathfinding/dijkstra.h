#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <compare>

#include "node.h"

class Dijkstra : public PathfindingAlgorithm {
private:
    Node* start;
    Node* end;
    std::unordered_map<Node*, Node*> came_from;
    std::unordered_map<Node*, int> g_score;
    std::unordered_set<Node*> open_set;
    std::unordered_set<Node*> closed_set;
    std::vector<Node*> path;

public:
    void setup(Grid& grid, Node* start, Node* end) override {
        this->start = start;
        this->end = end;
        came_from.clear();
        g_score.clear();
        open_set.clear();
        closed_set.clear();
        path.clear();

        g_score[start] = 0;
        open_set.insert(start);
    }

    bool step(Grid& grid) override {
        if (open_set.empty()) {
            return false;
        }

        // Find the node in the open set with the lowest g-score
        auto current = *std::min_element(open_set.begin(), open_set.end(), [&](Node* a, Node* b) {
            int g_score_a = INT_MAX;
            int g_score_b = INT_MAX;

            if (g_score.count(a) > 0) {
                g_score_a = g_score[a];
            }

            if (g_score.count(b) > 0) {
                g_score_b = g_score[b];
            }

            return g_score_a < g_score_b;
            });

        open_set.erase(current);
        closed_set.insert(current);

        for (auto neighbor : grid.get_neighbors(current)) {
            if (closed_set.count(neighbor) > 0 || neighbor->obstacle) {
                continue;
            }

            int tentative_g_score = g_score[current] + grid.get_edge_cost(current, neighbor);

            if (!g_score.count(neighbor) || tentative_g_score < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;

                if (open_set.count(neighbor) == 0) {
                    open_set.insert(neighbor);
                }
            }
        }

        return true;
    }

    std::vector<Node*> get_path() override {
        if (path.empty()) {
            Node* current = end;
            while (current != start) {
                path.push_back(current);
                if (came_from.find(current) != came_from.end()) {
                    current = came_from[current];
                }
                else {
                    break;  // or throw an exception
                }
            }
            path.push_back(start); // add the start node to the path
            std::reverse(path.begin(), path.end());
        }
        return path;
    }

    std::unordered_set<Node*> get_visited_nodes() override {
        return closed_set;
    }
};


