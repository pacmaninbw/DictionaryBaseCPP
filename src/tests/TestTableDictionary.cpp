#include <iostream>
#include "TableDictionary.h"
#include "TestTableDictionary.h"

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

    for (auto testCandidate: TTestData)
    {
        if (!testIdToName(testCandidate.testID, testCandidate.testNames))
        {
            return false;
        }
        if (!testNamesToID(testCandidate.testNames, testCandidate.testID))
        {
            return false;
        }
        if (!testNameToID(testCandidate.testNames.first, testCandidate.testID))
        {
            return false;
        }
        if (!testNameToID(testCandidate.testNames.second, testCandidate.testID))
        {
            return false;
        }
    }

    // Negative Test Path
    if (!testIdToName(static_cast<TableIds>(217), {"",""}))
    {
        return false;
    }
    if (!testNamesToID(std::pair("Name Not Found", "bad"), TableIds::NO_TABLE))
    {
        return false;
    }
    if (!testNameToID("Name Not Found", TableIds::NO_TABLE))
    {
        return false;
    }

    return allTestsPassed;
}

bool TestTableDictionary::testNamesToID(std::pair<std::string, std::string> input, TableIds expectedOutput) noexcept
{
    TableDictionary underTest;
    TableIds actualOutPut = underTest.getIds(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tTable Name to ID Test Failed (" << input.first << " " << input.second << ")\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::testNameToID(std::string input, TableIds expectedOutput) noexcept
{
    TableDictionary underTest;
    TableIds actualOutPut = underTest.getId(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tSingle Table Name to ID Test Failed " << input << "\n";
        return false;
    }

    return true;
}

bool TestTableDictionary::testIdToName(TableIds input, std::pair<std::string, std::string> expectedOutput) noexcept
{
    TableDictionary underTest;
    std::pair<std::string, std::string> actualOutPut(underTest.getNames(input));

    if (expectedOutput.first.compare(actualOutPut.first) != 0 || 
            expectedOutput.second.compare(actualOutPut.second) != 0)
    {
        std::cerr << "\tTable ID to Name Test Failed  (" << expectedOutput.first << " " << expectedOutput.second << ")\n";
        return false;
    }

    return true;
}
