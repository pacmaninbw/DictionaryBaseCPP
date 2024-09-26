#include <iostream>
#include "ColumnDictionary.h"
#include "TestColumnDictionary.h"

/*
 * Testing the ColumnDictionary class, which just uses the base class.
 */

TestColumnDictionary::TestColumnDictionary()
{
    positiveColumnTestData = 
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
}

bool TestColumnDictionary::executeTests() noexcept
{
    bool allTestsPassed = true;

    std::cout << "\nTesting ColumnDictionary\n";

    for (auto testCandidate: positiveColumnTestData)
    {
        if (!testIdToName(testCandidate.testId, testCandidate.testName))
        {
            return false;
        }
        if (!testNameToID(testCandidate.testName, testCandidate.testId))
        {
            return false;
        }
    }

    std::cout << "\tAll Positive Path Tests Passed\n";

    // Negative Test Path
    if (!testIdToName(static_cast<ColumnIds>(217), ""))
    {
        std::cout << "Negative Path Tests for ID to Name FAILED\n";
        return false;
    }
    if (!testNameToID("Name Not Found", ColumnIds::NO_COLUMN))
    {
        std::cout << "Negative Path Tests for Name to ID FAILED\n";
        return false;
    }
    std::cout << "\tAll Negative Path Tests Passed\n";

    return allTestsPassed;
}

bool TestColumnDictionary::testIdToName(ColumnIds input, std::string expectedOutput) noexcept
{
    try
    {
        ColumnDictionary underTest;
        std::string actualOutPut = underTest.getNames(input);

        if (!expectedOutput.compare(actualOutPut) == 0)
        {
            std::cerr << "Column ID to Name Test Failed " << expectedOutput << "\n";
            return false;
        }
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "TestColumnDictionary::testIdToName() logic_error: " << le.what() << "\n\n";
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestColumnDictionary::testIdToName() UNEXPECTED EXCEPTION: " << e.what() << '\n';
        return false;
    }
    
    return true;
}

bool TestColumnDictionary::testNameToID(std::string input, ColumnIds expectedOutput) noexcept
{
    try
    {
        ColumnDictionary underTest;
        ColumnIds actualOutPut = underTest.getIds(input);

        if (expectedOutput != actualOutPut)
        {
            std::cerr << "\tColumn Name to ID Test Failed " << input << "\n";
            return false;
        }
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "TestColumnDictionary::testNameToID() logic_error: " << le.what() << "\n\n";
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestColumnDictionary::testNameToID() UNEXPECTED EXCEPTION: " << e.what() << '\n';
        return false;
    }    

    return true;
}
