module;

#include <vector>;
#include <queue>;
#include <stack>;
#include <unordered_set>;
#include <unordered_map>;
#include <algorithm>;
#include <functional>;
#include <iostream>;

import node; 

export module astar;

import pathfindingalgorithm;

export class AStar : public PathfindingAlgorithm {
private:
    Node* start;
    Node* end;
    std::vector<Node*> path;
    std::unordered_map<Node*, Node*> came_from;
    std::unordered_map<Node*, int> g_score;
    std::unordered_map<Node*, int> f_score;
    std::vector<Node*> open_set;
    std::unordered_set<Node*> visited_nodes;

public:
    void setup(Grid& grid, Node* start, Node* end) override {
        this->start = start;
        this->end = end;
        came_from.clear();
        g_score.clear();
        f_score.clear();
        visited_nodes.clear();
        path.clear();
        open_set.clear();

        open_set.push_back(start);
        g_score[start] = 0;
        f_score[start] = start->heuristic(end);
    }

    bool step(Grid& grid) override {
        if (open_set.empty())
            return false;

        Node* current = *std::min_element(open_set.begin(), open_set.end(),
            [&](Node* a, Node* b) { return f_score[a] < f_score[b]; });

        if (current == end) {
            while (current != start) {
                current = came_from[current];
                path.push_back(current);
            }
            std::reverse(path.begin(), path.end());
            return false;
        }

        open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());
        visited_nodes.insert(current);

        for (auto neighbor : grid.get_neighbors(current)) {
            if (visited_nodes.count(neighbor) || neighbor->obstacle)
                continue;

            int tentative_g_score = g_score[current] + 1;

            if (!g_score.count(neighbor))
                open_set.push_back(neighbor);
            else if (tentative_g_score >= g_score[neighbor])
                continue;

            came_from[neighbor] = current;
            g_score[neighbor] = tentative_g_score;
            f_score[neighbor] = tentative_g_score + neighbor->heuristic(end);
        }

        return true;
    }

    std::unordered_set<Node*> get_visited_nodes() override {
        return visited_nodes;
    }

    std::vector<Node*> get_path() override {
        return path;
    }
};
