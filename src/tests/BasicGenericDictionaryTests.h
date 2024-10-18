#ifndef BASICGENERICDICTIONARYTESTS_H_
#define BASICGENERICDICTIONARYTESTS_H_

#include "../include/GenericDictionary.h"
#include <iostream>
#include <string>
#include <vector>
#include "UtilityTimer.h"

template <typename enumDictType>
static bool testIdToName(
	GenericDictionary<enumDictType, std::string>& underTest,
	enumDictType testID,
	std::string expectedOutput,
	std::string errorMessage
)
{
    std::string testGetName = underTest.getNames(testID);
    if (testGetName.compare(expectedOutput) != 0)
    {
        std::cerr
            << "\t" << errorMessage << " Input Value " <<
            static_cast<std::size_t>(testID)
            << " Expected Output " << expectedOutput << " " 
            << " Actual Ouput " << testGetName << "\n";
            ;
        return false;
    }

    return true;
}

template <typename enumDictType>
static bool testNameToID(
	GenericDictionary<enumDictType, std::string>& underTest,
	std::string testName,
	enumDictType expectedOutput,
	std::string errorMessage
	)
{
    enumDictType testGetID = underTest.getIds(testName);
    if (testGetID != expectedOutput)
    {
        std::cerr <<
            "\t " << errorMessage << " get ID from Name FAILED: "
            << "Input Name: " << testName
            << " Expected Output: " << static_cast<std::size_t>(expectedOutput)
            << " Actual Output: " << static_cast<std::size_t>(testGetID)
            << "\n";
        return false;
    }

    return true;
}

template <typename  enumDictType> using TestPairs = GenricDictionaryDataPair<enumDictType, std::string>;

template <typename enumDictType>
static bool testIDtoNameLoop(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<GenricDictionaryDataPair<enumDictType, std::string>>& TestData,
    std::string errorMessage
)
{
    bool allTestsPassed = true;

    for (auto test: TestData)
    {
        enumDictType testId = test.id;
        std::string expectedOutPut = test.names;
        std::string testGetName = underTest.getNames(testId);
        if (testGetName.compare(expectedOutPut) != 0)
        {
            std::cerr
                << "\t" << errorMessage << " Input Value " <<
                static_cast<std::size_t>(testId)
                << " Expected Output " << expectedOutPut << " " 
                << " Actual Ouput " << testGetName << "\n";
                ;
            allTestsPassed = false;
            break;
        }
    }

    return allTestsPassed;
}

template <typename enumDictType>
static bool testNametoIDLoop(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<GenricDictionaryDataPair<enumDictType, std::string>>& localTestData,
    std::string errorMessage
)
{
    bool allTestsPassed = true;

    for (auto test: localTestData)
    {
        std::string testName = test.names;
        enumDictType expectedOutput = test.id;
        enumDictType testGetID = underTest.getIds(testName);
        if (testGetID != expectedOutput)
        {
            std::cerr <<
                "\t " << errorMessage << " get ID from Name FAILED: "
                << "Input Name: " << testName
                << " Expected Output: " << static_cast<std::size_t>(expectedOutput)
                << " Actual Output: " << static_cast<std::size_t>(testGetID)
                << "\n";
            allTestsPassed = false;
            break;
        }
    }

    return allTestsPassed;
}

template <typename enumDictType>
static bool testMinMaxMiddleValues(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<TestPairs<enumDictType>>& testData,
    std::string testName
)
{
    bool allTestsPassed = true;
    UtilityTimer testTimer;

    std::vector<std::size_t> indexes;
    indexes.push_back(static_cast<std::size_t>(testData.size() - 1));
    if (testData.size() > 10)
    {
        indexes.push_back(static_cast<std::size_t>((testData.size() * 0.75) - 1));
        indexes.push_back(static_cast<std::size_t>((testData.size() * 0.5) - 1));
        indexes.push_back(static_cast<std::size_t>((testData.size() * 0.25) -1));
    }
    indexes.push_back(0);

    for (auto tIndex: indexes)
    {
        auto tDp = testData[tIndex];
        std::string testReport = "Performance Test find string from [" + std::to_string(tIndex) + "] ID " + testName + " ";
        testTimer.startTimer();
        allTestsPassed = testIdToName<enumDictType>(underTest, tDp.id, tDp.names, testName + " testIDToName()");
        testTimer.stopTimerAndReport(testReport);
        if (!allTestsPassed)
        {
            return false;
        }
    }

    for (auto tIndex: indexes)
    {
        auto tDp = testData[tIndex];
        std::string testReport = "Performance Test find ID from [" + std::to_string(tIndex) + "] Name " + testName + " ";
        testTimer.startTimer();
        allTestsPassed = testNameToID<enumDictType>(underTest, tDp.names, tDp.id, testName + " testNameToID()");
        testTimer.stopTimerAndReport(testReport);
        if (!allTestsPassed)
        {
            return false;
        }
    }

    return allTestsPassed;
}

template <typename enumDictType>
static bool performanceExecution(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<TestPairs<enumDictType>>& testData,
    std::string testName
)
{
    bool allTestsPassed = true;
    UtilityTimer testTimer;

    testMinMaxMiddleValues<enumDictType>(underTest, testData, testName);
    if (!allTestsPassed)
    {
        return false;
    }

    testTimer.startTimer();
    testIDtoNameLoop<enumDictType>(underTest, testData, testName + " testIDtoNameLoop()");
    testTimer.stopTimerAndReport("Performance Loop Test find string from ID " + testName + " ");
    if (!allTestsPassed)
    {
        return false;
    }

    testTimer.startTimer();
    testNametoIDLoop<enumDictType>(underTest, testData, testName + " testNametoIDLoop()");
    testTimer.stopTimerAndReport("Performance Loop Test find ID from Name " + testName + " ");
    if (!allTestsPassed)
    {
        return false;
    }

    return allTestsPassed;
}

#endif // BASICGENERICDICTIONARYTESTS_H_

