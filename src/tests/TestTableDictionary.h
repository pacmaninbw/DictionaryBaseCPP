#ifndef TESTTABLEDICTIONARY_H
#define TESTTABLEDICTIONARY_H

/*
 * Testing the TableDictionary class, which extends uses the base class.
 *
 * The TableDictionary class was selected for testing because it is being
 * used in another project.
 */

#include "tableidenum.h"
#include <string>
#include <utility>
#include <vector>
class TestTableDictionary
{
public:
    TestTableDictionary();
    ~TestTableDictionary() = default;
    bool executeTests() noexcept;

private:
    bool testNamesToID(std::pair<std::string, std::string> input, TableIds expectedOutput) noexcept;
    bool testNameToID(std::string input, TableIds expectedOutput) noexcept; 
    bool testIdToName(TableIds input, std::pair<std::string, std::string>  expectedOutput) noexcept;
    typedef struct TableIDTestData
    {
        TableIds testID;
        std::pair<std::string, std::string> testNames;
    } TableIDTestData;
    std::vector<TableIDTestData> TTestData;
};

#endif