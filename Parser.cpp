#include "Parser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<int> parseAccessSequence(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::vector<int> accesses;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        int key;

        if (!(iss >> key)) {
            throw std::runtime_error("Invalid line in file: " + line);
        }

        accesses.push_back(key);
    }

    return accesses;
}
