#ifndef TABLEDICTIONARY_H
#define TABLEDICTIONARY_H

#include "../include/GenericDictionary.h"
#include <string>
#include "tableidenum.h"
#include <utility>

class TableDictionary : public GenericDictionary<TableIds, std::pair<std::string, std::string>>
{
public:
    TableDictionary();
    std::string getShortName(TableIds sName) noexcept;
    std::string getTableName(TableIds lName) noexcept;
    TableIds getId(std::string name) noexcept;
};

#endif