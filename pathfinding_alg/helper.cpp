#include "helper.h"

std::string serialize_path(const std::vector<Node*>& path) {
    std::string result;
    for (const auto& node : path) {
        result += std::to_string(node->x) + ',' + std::to_string(node->y) + ';';
    }
    return result;
}
