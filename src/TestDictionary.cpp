#include "ColumnDictionary.h"
#include "columnidenum.h"
#include <iostream>
#include <string>
#include "TableDictionary.h"
#include <vector>

static bool TableTestIdToName(TableIds input, std::pair<std::string, std::string>  expectedOutput)
{
    TableDictionary underTest;
    std::pair<std::string, std::string> actualOutPut(underTest.getNames(input));

    std::cout << "actualOutPut " << actualOutPut.first << " " << actualOutPut.second << "\n";

    if (expectedOutput.first.compare(actualOutPut.first) != 0 || 
            expectedOutput.second.compare(actualOutPut.second) != 0)
    {
        std::cerr << "\tTable ID to Name Test Failed  (" << expectedOutput.first << " " << expectedOutput.second << ")\n";
        return false;
    }

    return true;
}

static bool TableTestNameToID(std::pair<std::string, std::string> input, TableIds expectedOutput)
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

static bool TableTestNameToID(std::string input, TableIds expectedOutput)
{
    TableDictionary underTest;
    TableIds actualOutPut = underTest.getId(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tSingl eTable Name to ID Test Failed " << input << "\n";
        return false;
    }

    return true;
}
typedef struct TableIDTestData
{
    TableIds testID;
    std::pair<std::string, std::string> testNames;
} TableIDTestData;

static std::vector<TableIDTestData> TTestData =
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

static bool testTableIdsDictionary()
{
    bool testPassed = true;

    std::cout << "\nTesting TableDictionary\n";

    for (auto testCandidate: TTestData)
    {
        if (!TableTestIdToName(testCandidate.testID, testCandidate.testNames))
        {
            return false;
        }
        if (!TableTestNameToID(testCandidate.testNames, testCandidate.testID))
        {
            return false;
        }
        if (!TableTestNameToID(testCandidate.testNames.first, testCandidate.testID))
        {
            return false;
        }
        if (!TableTestNameToID(testCandidate.testNames.second, testCandidate.testID))
        {
            return false;
        }
    }

    // Negative Test Path
    if (!TableTestIdToName(static_cast<TableIds>(217), {"",""}))
    {
        return false;
    }
    if (!TableTestNameToID(std::pair("Name Not Found", "bad"), TableIds::NO_TABLE))
    {
        return false;
    }
    if (!TableTestNameToID("Name Not Found", TableIds::NO_TABLE))
    {
        return false;
    }

    return testPassed;
}

static bool ColumnTestIdToName(ColumnIds input, std::string expectedOutput)
{
    ColumnDictionary underTest;
    std::string actualOutPut = underTest.getNames(input);

    if (!expectedOutput.compare(actualOutPut) == 0)
    {
        std::cerr << "Column ID to Name Test Failed " << expectedOutput << "\n";
        return false;
    }

    return true;
}

static bool ColumnTestNameToID(std::string input, ColumnIds expectedOutput)
{
    ColumnDictionary underTest;
    ColumnIds actualOutPut = underTest.getIds(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tColumn Name to ID Test Failed " << input << "\n";
        return false;
    }

    return true;
}

typedef struct CTestData
{
    ColumnIds testId;
    std::string testName;
} CTestData;

static std::vector<CTestData> positiveColumnTestData = 
{
    {ColumnIds::DATE, "Date"},
    {ColumnIds::TEMPERATURE, "Temperature"},
    {ColumnIds::PUSLE_RATE, "Pulse Rate"},
    {ColumnIds::RESPIRATION_RATE, "Respiration Rate"},
    {ColumnIds::BLOOD_PRESSURE, "Blood Pressure"},
    {ColumnIds::BLOOD_OXYGEN, "Blood Oxygen"},
    {ColumnIds::WEIGHT, "Weight"},
    {ColumnIds::BLOOD_SUGAR, "Blood Glucose"},
    {ColumnIds::EXERCISE, "Exercise"},
    {ColumnIds::SLEEP_HOURS, "Sleep Hours"},
    {ColumnIds::SLEEP_INTERRUPTIONS, "Sleep Interruptions"},
    {ColumnIds::BOWEL_MOVEMENTS, "Bowel Movements"},
    {ColumnIds::NUTRITION_CALORIES, "Calories"},
    {ColumnIds::NUTRITION_SATURATED_FAT, "Saturated Fat"},
    {ColumnIds::NUTRITION_TRANS_FAT, "Trans Fat"},
    {ColumnIds::NUTRITION_CHOLESTEROL, "Cholesterol"},
    {ColumnIds::NUTRITION_SODIUM, "Sodium"},
    {ColumnIds::NUTRITION_FIBER, "Fiber"},
    {ColumnIds::NUTRITION_TOTAL_SUGARS, "Total Sugars"},
    {ColumnIds::NUTRITION_PROTIEN, "Protien"},
    {ColumnIds::NUTRITION_VITAMIN_D, "Vitamin D"},
    {ColumnIds::NUTRITION_CALCIUM, "Calcium"},
    {ColumnIds::NUTRITION_IRON, "Iron"},
    {ColumnIds::NUTRITION_POTASSIUM, "Potassium"},
    {ColumnIds::NOTES, "Notes"}
};

static bool testColumnIdsDictionary()
{
    bool testPassed = true;
    std::cout << "\nTesting ColumnDictionary\n";

    for (auto testCandidate: positiveColumnTestData)
    {
        if (!ColumnTestIdToName(testCandidate.testId, testCandidate.testName))
        {
            return false;
        }
        if (!ColumnTestNameToID(testCandidate.testName, testCandidate.testId))
        {
            return false;
        }
    }

    // Negative Test Path
    if (!ColumnTestIdToName(static_cast<ColumnIds>(217), ""))
    {
        return false;
    }
    if (!ColumnTestNameToID("Name Not Found", ColumnIds::NO_COLUMN))
    {
        return false;
    }

    return testPassed;
}

int main()
{
    int exitStatus = EXIT_SUCCESS;

    if (!testColumnIdsDictionary())
    {
        exitStatus = EXIT_FAILURE;
    }

    if (!testTableIdsDictionary())
    {
        exitStatus = EXIT_FAILURE;
    }

    std::cout << (exitStatus == EXIT_FAILURE ? "Tests Failed\n\n" : "All Tests Passed\n\n");

    return exitStatus;
}
