#ifndef TESTCOLUMNDICTIONARY_H
#define TESTCOLUMNDICTIONARY_H

/*
 * Testing the ColumnDictionary class, which just uses the base class.
 *
 * The ColumnDictionary class was selected for testing because it is being
 * used in another project.
 */

#include "columnidenum.h"
#include <string>
#include <vector>

class TestColumnDictionary
{
public:
    TestColumnDictionary();
    ~TestColumnDictionary() = default;
    bool executeTests() noexcept;

private:
    bool testIdToName(ColumnIds input, std::string expectedOutput) noexcept;
    bool testNameToID(std::string input, ColumnIds expectedOutput) noexcept;
    typedef struct CTestData
    {
        ColumnIds testId;
        std::string testName;
    } CTestData;
    std::vector<CTestData> positiveColumnTestData;
};

#endif // TESTCOLUMNDICTIONARY_H