#include <iostream>
#include <string>
#include "command.hpp"
#include "table.hpp"
#include "row.hpp"

// Forward declaration
Command parseCommand(const std::string& input);
const std::string DB_FILE = "database.db";

int main() {
    std::string input;
    Table table;
    table.loadFromFile(DB_FILE);

    std::cout << "MiniDB started. Type `.exit` to quit.\n";
    while (true) {
        std::cout << "db > ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        if (input[0] == '.') {
            if (input == ".exit") {
                std::cout << "Exiting MiniDB...\n";
                break;
            } else {
                std::cout << "Unrecognized meta-command: " << input << "\n";
                continue;
            }
        }

        Command command = parseCommand(input);
switch (command.type) {
    case CommandType::INSERT:
        if (command.args.size() != 2) {
            std::cout << "Usage: INSERT <id> <name>\n";
            break;
        }
        try {
            int id = std::stoi(command.args[0]);
            std::string name = command.args[1];
            table.insert({id, name});
            table.saveToFile(DB_FILE);

        } catch (...) {
            std::cout << "Invalid ID format\n";
        }
        break;

    case CommandType::SELECT:
        table.selectAll();
        break;

    case CommandType::DELETE_:
        if (command.args.size() != 1) {
            std::cout << "Usage: DELETE <id>\n";
            break;
        }
        table.remove(std::stoi(command.args[0]));
        table.saveToFile(DB_FILE);

        break;

    case CommandType::UPDATE:
        if (command.args.size() != 2) {
            std::cout << "Usage: UPDATE <id> <new_name>\n";
            break;
        }
        table.update(std::stoi(command.args[0]), command.args[1]);
        table.saveToFile(DB_FILE);
        break;

    case CommandType::DROP:
        table.drop();
        table.saveToFile(DB_FILE);
        break;

    case CommandType::HELP:
        std::cout << "Supported commands:\n"
                     "  INSERT <id> <name>\n"
                     "  SELECT\n"
                     "  DELETE <id>\n"
                     "  UPDATE <id> <new_name>\n"
                     "  DROP\n"
                     "  HELP\n"
                     "  .exit\n";
        break;

        default:        
        std::cout << "Unrecognized SQL command\n";
}

    }

    return 0;
}
