#ifndef ABSTRACTDICTIONARY_H_
#define ABSTRACTDICTIONARY_H_

#include <algorithm>
#include <vector>

/*
 * This abstract class provides a basic conversion of enums or integers to strings.
 * More complex objects than strings are also supported, however, overrides will
 * be necessary;
 * 
 * Enums or integers should have an illegal value as 0. If not, then override the
 * getIds method.
 */
template <typename dicID, typename dicName>
class DictionaryBase
{
public:
    virtual dicID getIds(dicName itemName) noexcept
    {
        dicID foundID = static_cast<dicID>(0);

        auto definition = std::find_if(searchTable.begin(), searchTable.end(),
            [&itemName](struct DictType &dicItem) {return (dicItem.names == itemName);});

        if (definition != searchTable.end())
        {
            foundID = definition->id;
        }

        return foundID;
    };
    virtual dicName getNames(dicID id) noexcept
    {
        dicName nameFound;

        auto definition = std::find_if(searchTable.begin(), searchTable.end(),
            [&id](struct DictType &dicItem) {return (dicItem.id == id);});

        if (definition != searchTable.end())
        {
            nameFound = definition->names;
        }

        return nameFound;
    }
    virtual bool noOverRidesNeed() noexcept = 0;

protected:
    struct DictType
    {
        dicID id;
        dicName names;
    };
    std::vector<DictType> searchTable;
    void addDefinition(dicID inId, dicName inName) noexcept
    {
        DictType newDef(inId, inName);
        searchTable.push_back(newDef);
    }


};

#endif // ABSTRACTDICTIONARY_H_