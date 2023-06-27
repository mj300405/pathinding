module;

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

export module node;

export class Node {
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
