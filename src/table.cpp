#include "table.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

bool Table::insert(const Row& row) {
    if (rows_.count(row.id)) {
        std::cerr << "Error: Duplicate ID " << row.id << "\n";
        return false;
    }
    rows_[row.id] = row;
    return true;
}

bool Table::update(int id, const std::string& newName) {
    if (!rows_.count(id)) {
        std::cerr << "Error: ID " << id << " not found\n";
        return false;
    }
    rows_[id].name = newName;
    return true;
}       

bool Table::saveToFile(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) return false;

    for (const auto& [id, row] : rows_) {
        out.write(reinterpret_cast<const char*>(&id), sizeof(int));

        char buffer[32];
        std::memset(buffer, 0, sizeof(buffer));
        std::strncpy(buffer, row.name.c_str(), sizeof(buffer) - 1);

        out.write(buffer, sizeof(buffer));
    }

    out.close();
    return true;
}

bool Table::loadFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false;

    rows_.clear();
    while (in) {
        int id;
        char buffer[32];
        in.read(reinterpret_cast<char*>(&id), sizeof(int));
        in.read(buffer, sizeof(buffer));
        if (in.gcount() < sizeof(buffer)) break;

        rows_[id] = Row{id, std::string(buffer)};
    }

    in.close();
    return true;
}

bool Table::remove(int id) {
    if (!rows_.erase(id)) {
        std::cerr << "Error: ID " << id << " not found\n";
        return false;
    }
    return true;
}

void Table::drop() {
    rows_.clear();
    std::cout << "Table cleared.\n";
}

void Table::selectAll() const {
    if (rows_.empty()) {
        std::cout << "Table is empty.\n";
        return;
    }
    for (const auto& [id, row] : rows_) {
        std::cout << "(" << row.id << ", " << row.name << ")\n";
    }
}
