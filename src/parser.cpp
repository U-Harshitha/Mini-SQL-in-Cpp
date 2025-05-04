#include "command.hpp"
#include <sstream>
#include <algorithm>

Command parseCommand(const std::string& input) {
    std::istringstream stream(input);
    std::string word;
    std::vector<std::string> tokens;

    while (stream >> word) {
        tokens.push_back(word);
    }

    if (tokens.empty()) {
        return { CommandType::UNKNOWN, {} };
    }

    std::string cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

    if (cmd == "INSERT") {
        return { CommandType::INSERT, std::vector<std::string>(tokens.begin() + 1, tokens.end()) };
    } else if (cmd == "SELECT") {
        return { CommandType::SELECT, {} };
    } else if (cmd == "DELETE") {
        return { CommandType::DELETE_, std::vector<std::string>(tokens.begin() + 1, tokens.end()) };
    } else if (cmd == "UPDATE") {
        return { CommandType::UPDATE, std::vector<std::string>(tokens.begin() + 1, tokens.end()) };
    } else if (cmd == "DROP") {
        return { CommandType::DROP, {} };
    } else if (cmd == "HELP") {
        return { CommandType::HELP, {} };
    }

    return { CommandType::UNKNOWN, {} };
}
