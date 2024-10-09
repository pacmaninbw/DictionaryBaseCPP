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

class ColumnDictionary;

class TestColumnDictionary
{
public:
    TestColumnDictionary();
    ~TestColumnDictionary() = default;
    bool executeTests() noexcept;
    bool executeStandAloneTests() noexcept;
    bool executeCommonGDTests() noexcept;

private:
    bool commonGDIdToName(ColumnDictionary &underTest, ColumnIds input, std::string expectedOutput) noexcept;
    bool commonGDNameToID(ColumnDictionary &underTest, std::string input, ColumnIds expectedOutput) noexcept;
    bool standAloneIdToName(ColumnIds input, std::string expectedOutput) noexcept;
    bool standAloneNameToID(std::string input, ColumnIds expectedOutput) noexcept;
    struct CTestData
    {
        ColumnIds testId;
        std::string testName;
    };
    std::vector<CTestData> positiveColumnTestData;
};

#endif // TESTCOLUMNDICTIONARY_H