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

class TableDictionary;

class TestTableDictionary
{
public:
    TestTableDictionary();
    ~TestTableDictionary() = default;
    bool executeTests() noexcept;
    bool executeStandAloneTests() noexcept;
    bool executeCommonGDTests() noexcept;

private:
    bool commonGDTestNamesToID(TableDictionary &underTest, std::pair<std::string, std::string> input, TableIds expectedOutput) noexcept;
    bool commonGDTestNameToID(TableDictionary &underTest, std::string input, TableIds expectedOutput) noexcept; 
    bool commonGDTestIdToName(TableDictionary &underTest, TableIds input, std::pair<std::string, std::string>  expectedOutput) noexcept;
    bool standAloneTestNamesToID(std::pair<std::string, std::string> input, TableIds expectedOutput) noexcept;
    bool standAloneTestNameToID(std::string input, TableIds expectedOutput) noexcept; 
    bool standAloneTestIdToName(TableIds input, std::pair<std::string, std::string>  expectedOutput) noexcept;
    struct TableIDTestData
    {
        TableIds testID;
        std::pair<std::string, std::string> testNames;
    };
    std::vector<TableIDTestData> TTestData;
};

#endif