#include <string>
#include "TableDictionary.h"
#include <utility>

TableDictionary::TableDictionary()
{
    addDefinition(TableIds::TEMPURATURE, {"Tempurature", "tmp"});
    addDefinition(TableIds::REPIRATION_RATE, {"RepirationRate", "resp"});
    addDefinition(TableIds::BLOOD_PRESSURE, {"BloodPressure", "bp"});;
    addDefinition(TableIds::BLOOD_OXYGEN, {"BloodOxygen", "bo"});
    addDefinition(TableIds::WEIGHT, {"Weight", "wt"});
    addDefinition(TableIds::BLOOD_SUGAR, {"BloodSugar", "bg"});
    addDefinition(TableIds::EXERCISE, {"Exercise", "exer"});
    addDefinition(TableIds::SLEEP, {"Sleep", "slp"});
    addDefinition(TableIds::BOWEL_MOVEMENTS, {"BowlMovements", "bm"});
    addDefinition(TableIds::NUTRITION, {"Nutrition", "nut"});
    addDefinition(TableIds::NOTES, {"Notes", "nts"});
}

std::string TableDictionary::getShortName(TableIds key) noexcept
{
    return getNames(key).second;
}

std::string TableDictionary::getTableName(TableIds key) noexcept
{
    return getNames(key).first;
}

TableIds TableDictionary::getId(std::string key) noexcept
{
    TableIds id = TableIds::NO_TABLE;

    auto definition = std::find_if(searchTable.begin(), searchTable.end(),
        [&key](struct DictType &dicItem) {
            return (dicItem.names.first == key ||
            dicItem.names.second == key);
        });

    if (definition != searchTable.end())
    {
        id = definition->id;
    }

    return id;
}
