#pragma once
#include <string>
#include <vector>

enum class CommandType {
    INSERT,
    SELECT,
    DELETE_,
    UPDATE,
    DROP,
    HELP,
    UNKNOWN
};

struct Command {
    CommandType type;
    std::vector<std::string> args;
};
