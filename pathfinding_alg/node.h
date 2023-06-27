#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <compare>
#include <ranges>



class Node {
public:
    int x;
    int y;
    bool visited;
    bool obstacle;
    int id;
    inline static int next_id;

    Node() : x(0), y(0), visited(false), obstacle(false), id(next_id++) {}

    Node(int x, int y) : x(x), y(y), visited(false), obstacle(false), id(next_id++) {}

    // A* search heuristic function
    int heuristic(Node* other) {
        int dx = std::abs(x - other->x);
        int dy = std::abs(y - other->y);
        return (dx + dy);
    }

    void make_obstacle() {
        obstacle = true;
    }

    bool operator==(const Node* other) {
        return (x == other->x) && (y == other->y);
    }

    int getX() const { return x; }

    int getY() const { return y; }
};


class Grid {
private:
    Node* start;
    Node* end;
    int width;
    int height;
    std::vector<Node> nodes;

public:
    Grid(int w, int h) : width(w), height(h), nodes(w* h) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                nodes[y * width + x] = Node(x, y);
            }
        }
    }

    // Copy constructor
Grid(const Grid& other)
    : width(other.width), height(other.height), nodes(other.nodes) {
    // Copy start and end nodes
    start = get_node(other.start->x, other.start->y);
    end = get_node(other.end->x, other.end->y);
}


    Grid(int w, int h, int start_x, int start_y, int end_x, int end_y)
        : width(w), height(h), nodes(w* h) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                nodes[y * width + x] = Node(x, y);
            }
        }
        start = get_node(start_x, start_y);
        end = get_node(end_x, end_y);
    }

    void set_start(Node* s) {
        if (s != nullptr && s->x < width && s->y < height)
            start = s;
    }

    void set_end(Node* e) {
        if (e != nullptr && e->x < width && e->y < height)
            end = e;
    }

    Node* get_node(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return nullptr;
        }
        return &nodes[y * width + x];
    }

    Node* get_start_node() { return start; }

    Node* get_end_node() { return end; }

    /*std::vector<Node*> get_neighbors(Node* node) {
        static const std::pair<int, int> offsets[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        auto neighbors = offsets
            | std::views::transform([=](auto offset) {
            return get_node(node->x + offset.first, node->y + offset.second);
                })
            | std::views::filter([](auto neighbor) {
                    return neighbor != nullptr;
                });

                return std::vector<Node*>(neighbors.begin(), neighbors.end());
    }*/

    std::vector<Node*> get_neighbors(Node* node) {
        static const std::pair<int, int> offsets[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        std::vector<Node*> neighbors;

        for (const auto& offset : offsets) {
            Node* neighbor = get_node(node->x + offset.first, node->y + offset.second);
            if (neighbor != nullptr) {
                neighbors.push_back(neighbor);
            }
        }

        return neighbors;
    }


    double get_edge_cost(Node* node1, Node* node2) {
        // Compute the Euclidean distance between the nodes
        double dx = node2->x - node1->x;
        double dy = node2->y - node1->y;
        double distance = sqrt(dx * dx + dy * dy);

        // Return the distance as the edge cost
        return distance;
    }

    int get_width() const { return width; } // Assuming you have a width field

    int get_height() const { return height; } // Assuming you have a height field

};

class PathfindingAlgorithm {
public:
    virtual void setup(Grid& grid, Node* start, Node* end) = 0;
    virtual bool step(Grid& grid) = 0;
    virtual std::vector<Node*> get_path() = 0;
    virtual std::unordered_set<Node*> get_visited_nodes() = 0;
};
