#ifndef TESTGENERICDICTIONARY_H
#define TESTGENERICDICTIONARY_H

#include "../include/GenericDictionary.h"
#include <string>

/*
 * GD for GenericDictionary
 */
enum class GDPositivePathEnum
{
    GDPOSITIVE_INVALID_VALUE,
    GDPOSITIVE_TEST_VALUE_1,
    GDPOSITIVE_TEST_VALUE_2,
    GDPOSITIVE_TEST_VALUE_3,
    GDPOSITIVE_TEST_VALUE_4,
    GDPOSITIVE_TEST_VALUE_5,
    GDPOSITIVE_TEST_VALUE_6,
    GDPOSITIVE_LAST_ENUM
};

struct TestPairs
{
    GDPositivePathEnum testID;
    std::string testName;
};

class TestGenericDictionary
{
public:
    TestGenericDictionary();
    ~TestGenericDictionary() = default;
    bool executeTests() noexcept;

private:
    bool testContructorPositivePath() noexcept;
    bool testConstructorMissingIDDef() noexcept;
    bool testConstructorDuplicateID() noexcept;
    bool testConstructorDuplicateName() noexcept;
    bool testIdToName(GenericDictionary<GDPositivePathEnum, std::string> &underTest,
        GDPositivePathEnum testId, std::string &expectedOutput) noexcept;
    bool testIdToNameLoop(GenericDictionary<GDPositivePathEnum, std::string> &underTest,
        std::vector<TestPairs> &testData) noexcept;
    bool testNameToId(GenericDictionary<GDPositivePathEnum, std::string> &underTest,
        std::string testName, GDPositivePathEnum expectedOutput) noexcept;
    bool testNameToIDLoop(GenericDictionary<GDPositivePathEnum, std::string> &underTest,
        std::vector<TestPairs> &testData) noexcept;

};

#endif // TESTGENERICDICTIONARY_H