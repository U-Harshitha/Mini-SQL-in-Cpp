#pragma once

#include <map>
#include "row.hpp"

class Table {
public:
    bool insert(const Row& row);
    bool update(int id, const std::string& newName);
    bool remove(int id);
    void drop();
    void selectAll() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
private:
    std::map<int, Row> rows_;
};
