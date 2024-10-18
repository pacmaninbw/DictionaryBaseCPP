#include <iostream>
#include "TableDictionary.h"
#include "TestTableDictionary.h"
#include "../include/UtilityTimer.h"

/*
 * Testing TableDictionary class which adds some extenstions to the base clase.
 */

TestTableDictionary::TestTableDictionary()
{
    TTestData =
    {
        {TableIds::TEMPURATURE, {"Tempurature", "tmp"}},
        {TableIds::REPIRATION_RATE, {"RepirationRate", "resp"}},
        {TableIds::BLOOD_PRESSURE, {"BloodPressure", "bp"}},
        {TableIds::BLOOD_OXYGEN, {"BloodOxygen", "bo"}},
        {TableIds::WEIGHT, {"Weight", "wt"}},
        {TableIds::BLOOD_SUGAR, {"BloodSugar", "bg"}},
        {TableIds::EXERCISE, {"Exercise", "exer"}},
        {TableIds::SLEEP, {"Sleep", "slp"}},
        {TableIds::BOWEL_MOVEMENTS, {"BowlMovements", "bm"}},
        {TableIds::NUTRITION, {"Nutrition", "nut"}},
        {TableIds::NOTES, {"Notes", "nts"}},
    };
}

bool TestTableDictionary::executeTests() noexcept
{
    bool allTestsPassed = true;
    UtilityTimer testTimer;

    std::cout << "\nTesting TableDictionary\n";
    testTimer.startTimer();
    allTestsPassed = executeCommonGDTests();
    testTimer.stopTimerAndReport("Execute Commom TableDictionary Test ");


    if (allTestsPassed)
    {
        testTimer.startTimer();
        allTestsPassed = executeStandAloneTests();
        testTimer.stopTimerAndReport("Execute Stand Alone TableDictionary Test ");
    }

    if (allTestsPassed)
    {
        std::cout << "\tAll Table Dictionary Tests Passed\n";
    }
    else
    {
        std::cout << "\tSome or all Table Dictionary Tests FAILED\n";
    }

    return allTestsPassed;
}

/*
 * In the stand alone tests each tests constructs a TableDicionary
 */
bool TestTableDictionary::executeStandAloneTests() noexcept
{
    std::cout << "\nTesting Stand Alone Table Dictionary\n";
    for (auto testCandidate: TTestData)
    {
        if (!standAloneTestIdToName(testCandidate.testID, testCandidate.testNames))
        {
            return false;
        }
        if (!standAloneTestNamesToID(testCandidate.testNames, testCandidate.testID))
        {
            return false;
        }
        if (!standAloneTestNameToID(testCandidate.testNames.first, testCandidate.testID))
        {
            return false;
        }
        if (!standAloneTestNameToID(testCandidate.testNames.second, testCandidate.testID))
        {
            return false;
        }
    }

    // Negative Test Path
    if (!standAloneTestIdToName(static_cast<TableIds>(217), {"",""}))
    {
        return false;
    }
    if (!standAloneTestNamesToID(std::pair("Name Not Found", "bad"), TableIds::NO_TABLE))
    {
        return false;
    }
    if (!standAloneTestNameToID("Name Not Found", TableIds::NO_TABLE))
    {
        return false;
    }

    std::cout << "\tAll Stand Alone TableDictionary Tests PASSED\n";

    return true;
}

/*
 * In the common GenericDicitonary tests a TableDictionary is constructed
 * once and used in each test execution.
 */
bool TestTableDictionary::executeCommonGDTests() noexcept
{
    TableDictionary underTest;
    std::cout << "\nTesting Common Table Dictionary\n";
    for (auto testCandidate: TTestData)
    {
        if (!commonGDTestIdToName(underTest, testCandidate.testID, testCandidate.testNames))
        {
            return false;
        }
        if (!commonGDTestNamesToID(underTest, testCandidate.testNames, testCandidate.testID))
        {
            return false;
        }
        if (!commonGDTestNameToID(underTest, testCandidate.testNames.first, testCandidate.testID))
        {
            return false;
        }
        if (!commonGDTestNameToID(underTest, testCandidate.testNames.second, testCandidate.testID))
        {
            return false;
        }
    }

    // Negative Test Path
    if (!commonGDTestIdToName(underTest, static_cast<TableIds>(217), {"",""}))
    {
        return false;
    }
    if (!commonGDTestNamesToID(underTest, std::pair("Name Not Found", "bad"), TableIds::NO_TABLE))
    {
        return false;
    }
    if (!commonGDTestNameToID(underTest, "Name Not Found", TableIds::NO_TABLE))
    {
        return false;
    }

    std::cout << "\tAll Common TableDictionary Tests PASSED\n";

    return true;
}

bool TestTableDictionary::commonGDTestNamesToID(TableDictionary &underTest, std::pair<std::string, std::string> input, TableIds expectedOutput) noexcept
{
    TableIds actualOutPut = underTest.getIds(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tCommon TableDictionary Table Names to ID Test Failed ("
            << input.first << " " << input.second << ")\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::commonGDTestNameToID(TableDictionary &underTest, std::string input, TableIds expectedOutput) noexcept
{
    TableIds actualOutPut = underTest.getId(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tCommon TableDictionary Single Table Name to ID Test Failed "
            << input << "\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::commonGDTestIdToName(TableDictionary &underTest, TableIds input, std::pair<std::string, std::string> expectedOutput) noexcept
{
    std::pair<std::string, std::string> actualOutPut(underTest.getNames(input));

    if (expectedOutput.first.compare(actualOutPut.first) != 0 || 
            expectedOutput.second.compare(actualOutPut.second) != 0)
    {
        std::cerr << "\tCommon TableDictionary Table ID to Name Test Failed  ("
            << expectedOutput.first << " " << expectedOutput.second << ")\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::standAloneTestNamesToID(std::pair<std::string, std::string> input, TableIds expectedOutput) noexcept
{
    TableDictionary underTest;
    TableIds actualOutPut = underTest.getIds(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tStand Alone Table Name to ID Test Failed ("
            << input.first << " " << input.second << ")\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::standAloneTestNameToID(std::string input, TableIds expectedOutput) noexcept
{
    TableDictionary underTest;
    TableIds actualOutPut = underTest.getId(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tStand Alone Single Table Name to ID Test Failed "
            << input << "\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::standAloneTestIdToName(TableIds input, std::pair<std::string, std::string> expectedOutput) noexcept
{
    TableDictionary underTest;
    std::pair<std::string, std::string> actualOutPut(underTest.getNames(input));

    if (expectedOutput.first.compare(actualOutPut.first) != 0 || 
            expectedOutput.second.compare(actualOutPut.second) != 0)
    {
        std::cerr << "\tStand Alone Table ID to Name Test Failed  ("
            << expectedOutput.first << " " << expectedOutput.second << ")\n";
        return false;
    }

    return true;
}
