#ifndef COLUMNDICTIONARY_H_
#define COLUMNDICTIONARY_H_

#include "../include/GenericDictionary.h"
#include "columnidenum.h"
#include <string>

class ColumnDictionary : public GenericDictionary<ColumnIds, std::string>
{
    public:
    ColumnDictionary();
};

#endif //COLUMNDICTIONARY_H_