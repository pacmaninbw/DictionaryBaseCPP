#include <string>
#include "TableDictionary.h"
#include <utility>

TableDictionary::TableDictionary()
: GenericDictionary(TableIds::NO_TABLE, TableIds::LAST_TABLE_ID, 
    {
        {TableIds::TEMPURATURE, {"Tempurature", "tmp"}},
        {TableIds::REPIRATION_RATE, {"RepirationRate", "resp"}},
        {TableIds::BLOOD_PRESSURE, {"BloodPressure", "bp"}},
        {TableIds::BLOOD_OXYGEN, {"BloodOxygen", "bo"}},
        {TableIds::WEIGHT, {"Weight", "wt"}},
        {TableIds::BLOOD_SUGAR, {"BloodSugar", "bg"}},
        {TableIds::EXERCISE, {"Exercise", "exer"}},
        {TableIds::SLEEP, {"Sleep", "slp"}},
        {TableIds::BOWEL_MOVEMENTS, {"BowlMovements", "bm"}},
        {TableIds::NUTRITION, {"Nutrition", "nut"}},
        {TableIds::NOTES, {"Notes", "nts"}}
    })
{
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
        [&key](DictType &dicItem) {
            return (dicItem.names.first == key ||
            dicItem.names.second == key);
        });

    if (definition != searchTable.end())
    {
        id = definition->id;
    }

    return id;
}
