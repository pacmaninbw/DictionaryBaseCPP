#ifndef GENERICDICTIONARY_H_
#define GENERICDICTIONARY_H_

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * This class provides a basic conversion of enums or integers to strings. The
 * class can be used as is, or as a base for a more complex object.
 * 
 * More complex objects than strings are also supported, however, overrides will
 * be necessary.
 * 
 * This class makes an attempt to find any missing definitions during construction.
 * 
 * Enums or integers should have an illegal value as 0. If not, then override the
 * getIds method.
 * 
 * The code has been modified based on a Code Review
 * https://codereview.stackexchange.com/questions/293782/generic-c-class-to-associate-enum-values-with-strings-for-translation
 * Changes since the review
 * - A constructor and destructor have been added.
 * - The constructor checks for missing definitions
 * - The class is no longer abstract
 * - dicID became dictID and dicName became dictName
 * 
 */
template <typename dictID, typename dictName>
class GenericDictionary
{
public:
    struct DictType
    {
        dictID id;
        dictName names;
    };

// Both the MinValue and MaxValue should be invalid values
// Example
// GenericDictionary(enum::NO_VALUE, enum::LAST_VALUE)
    GenericDictionary(dictID MinValue, dictID MaxValue, std::initializer_list<DictType> definitions)
    : MinimumValue{MinValue},
    MaximumValue{MaxValue},
    searchTable{definitions}
    {
        constructorMissingIDSizeTest();
        
        // To improve performance when searhing by id sort by id.
        // This sort is only necessary if the underlying structure remains
        // a vector. If it is std::map() the sort is not necessary.
        std::sort(searchTable.begin(), searchTable.end(),
            [](DictType a, DictType b) {return  a.id < b.id;});

        // Check for any missing definitions now that the data is sorted.
        for (auto b = searchTable.begin() + 1; b < searchTable.end(); b++ )
        {
            auto a = b - 1;
            if (static_cast<std::size_t>(a->id) != (static_cast<std::size_t>(b->id) - 1))
            {
                std::logic_error orderError("In GenericDictionary Constructor missing definion value " +
                    std::to_string((static_cast<std::size_t>(b->id) - 1)));
                    throw orderError;
            }
        }
    }

    virtual ~GenericDictionary() = default;

    virtual dictID getIds(dictName itemName) noexcept
    {
        auto definition = std::find_if(searchTable.begin(), searchTable.end(),
            [&itemName](struct DictType &dicItem) {return (dicItem.names == itemName);});

        if (definition != searchTable.end())
        {
            return definition->id;
        }

        return static_cast<dictID>(MinimumValue);
    };

    virtual dictName getNames(dictID id) noexcept
    {
        if (MinimumValue > id || id < MaximumValue)
        {
            auto definition = std::ranges::find(searchTable, id, &DictType::id);
            if (definition != searchTable.end())
            {
                return definition->names;
            }
        }

        dictName nameNotFound;
        return nameNotFound;
    }

    [[nodiscard]] bool addDefinition(dictID id, dictName name) noexcept
    {
        DictType newDef(id, name);
        if (!alreadyDefined(newDef))
        {
            searchTable.push_back(newDef);
            return true;
        }

        return false;
    }

protected:
/*
 * If the enum was constructed correctly, there are 2 enums defined that do not
 * have associated strings, the first enum, that has a zero value and the last
 * enum that can be used to calculate the number of enums.
 */
    void constructorMissingIDSizeTest()
    {
        std::size_t expectedSize = static_cast<std::size_t>(MaximumValue);
        expectedSize -= 1;
        if (searchTable.size() != expectedSize)
        {
            std::logic_error missingDefinitions("In GenericDictionary Constructor missing definion values");
                throw missingDefinitions;
        }
    }

    bool hasID(dictID id) noexcept
    {
        std::size_t countID = std::ranges::count(searchTable, id, &DictType::id);
        return (countID > 0);
    }

    bool hasName(dictName name) noexcept
    {
        std::size_t countID = std::ranges::count(searchTable, name, &DictType::names);
        return (countID > 0);
    }

    bool alreadyDefined(DictType candidate) noexcept
    {
        return hasID(candidate.id) || hasName(candidate.names);
    }

    bool hasDuplicateIds()
    {
        for (auto defintion: searchTable)
        {
            std::size_t countID = std::ranges::count(searchTable, defintion->id, &DictType::id);
            if (countID > 1)
            {
                return true;
            }
        }

        return false;
    }

    bool hasDuplicateNames()
    {
        for (auto defintion: searchTable)
        {
            std::size_t countNames = std::ranges::count(searchTable, defintion->names, &DictType::names);
            if (countNames > 1)
            {
                return true;
            }
        }

        return false;
    }

    dictID MinimumValue;
    dictID MaximumValue;
    // This is currently implemented using std::vector to
    // the avoid multiple allocations on the heap using
    // std::map
    std::vector<DictType> searchTable;
};

#endif // GENERICDICTIONARY_H_