module;

#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <unordered_map>

export module config_parser;

export class ConfigParser {
public:
    ConfigParser() = default;

    std::unordered_map<std::string, int> parse_config_file(const std::string& filename) {
        std::unordered_map<std::string, int> config;
        std::ifstream file(filename);
        std::regex config_pattern(R"(^(\w+): (\d+)$)");

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::smatch matches;
                if (std::regex_search(line, matches, config_pattern) && matches.size() > 2) {
                    config[matches[1]] = std::stoi(matches[2]);
                }
            }
        }

        return config;
    }
};


//width: 10
//height : 10
//startNode : 1
//endNode : 99