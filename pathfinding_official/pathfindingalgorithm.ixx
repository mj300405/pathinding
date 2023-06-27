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

export module pathfindingalgorithm;

import grid;
import node;


export class PathfindingAlgorithm {
public:
    virtual void setup(Grid& grid, Node* start, Node* end) = 0;
    virtual bool step(Grid& grid) = 0;
    virtual std::vector<Node*> get_path() = 0;
    virtual std::unordered_set<Node*> get_visited_nodes() = 0;
};
