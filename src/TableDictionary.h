#ifndef TABLEDICTIONARY_H
#define TABLEDICTIONARY_H

#include "AbstractDictionary.h"
#include <string>
#include "tableidenum.h"
#include <utility>

class TableDictionary : public DictionaryBase<TableIds, std::pair<std::string, std::string>>
{
public:
    TableDictionary();
    ~TableDictionary() = default;
    bool noOverRidesNeed() noexcept override { return false; }
    std::string getShortName(TableIds id) noexcept;
    std::string getTableName(TableIds key) noexcept;
    TableIds getId(std::string name) noexcept;
};

#endif