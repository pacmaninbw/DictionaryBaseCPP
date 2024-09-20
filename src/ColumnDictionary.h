#ifndef COLUMNDICTIONARY_H_
#define COLUMNDICTIONARY_H_

#include "AbstractDictionary.h"
#include "columnidenum.h"
#include <string>

class ColumnDictionary : public DictionaryBase<ColumnIds, std::string>
{
    public:
    ColumnDictionary();
    ~ColumnDictionary() = default;
    bool noOverRidesNeed() noexcept override { return true; }
};

#endif //COLUMNDICTIONARY_H_