#include <iostream>
#include "ColumnDictionary.h"
#include "TestColumnDictionary.h"
#include "../include/UtilityTimer.h"

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
    UtilityTimer testTimer;

    std::cout << "\nTesting ColumnDictionary\n";
    testTimer.startTimer();
    allTestsPassed = executeCommonGDTests();
    testTimer.stopTimerAndReport("Execute Commom ColumnDictionary Test ");


    if (allTestsPassed)
    {
        testTimer.startTimer();
        allTestsPassed = executeStandAloneTests();
        testTimer.stopTimerAndReport("Execute Stand Alone ColumnDictionary Test ");
    }

    if (allTestsPassed)
    {
        std::cout << "\tAll Column Dictionary Tests Passed\n";
    }
    else
    {
        std::cout << "\tSome or all Column Dictionary Tests FAILED\n";
    }

    return allTestsPassed;
}

/*
 * Each stand alone test creates a local copy of a ColumnDictionary
 */
bool TestColumnDictionary::executeStandAloneTests() noexcept
{
    bool allTestsPassed = true;

    std::cout << "\nTesting ColumnDictionary\n";

    for (auto testCandidate: positiveColumnTestData)
    {
        if (!standAloneIdToName(testCandidate.testId, testCandidate.testName))
        {
            return false;
        }
        if (!standAloneNameToID(testCandidate.testName, testCandidate.testId))
        {
            return false;
        }
    }

    std::cout << "\tAll Stand Alone Positive Path Tests Passed\n";

    // Negative Test Path
    if (!standAloneIdToName(static_cast<ColumnIds>(217), ""))
    {
        std::cout << "Stand Alone Negative Path Tests for ID to Name FAILED\n";
        return false;
    }
    if (!standAloneNameToID("Name Not Found", ColumnIds::NO_COLUMN))
    {
        std::cout << "Stand Alone Negative Path Tests for Name to ID FAILED\n";
        return false;
    }
    std::cout << "\tAll Stand Alone Negative Path Tests Passed\n";

    return allTestsPassed;
}

bool TestColumnDictionary::executeCommonGDTests() noexcept
{
    bool allTestsPassed = true;
    std::cout << "\nTesting Common Dictionary ColumnDictionary\n";
    try
    {
        ColumnDictionary underTest;

        for (auto testCandidate: positiveColumnTestData)
        {
            if (!commonGDIdToName(underTest, testCandidate.testId, testCandidate.testName))
            {
                return false;
            }
            if (!commonGDNameToID(underTest, testCandidate.testName, testCandidate.testId))
            {
                return false;
            }
        }
        std::cout << "\tAll Common ColumnDictionary Positive Path Tests Passed\n";

        // Negative Test Path
        if (!commonGDIdToName(underTest, static_cast<ColumnIds>(217), ""))
        {
            std::cout << "\tCommon ColumnDictionary Negative Path Tests for ID to Name FAILED\n";
            return false;
        }
        if (!commonGDNameToID(underTest, "Name Not Found", ColumnIds::NO_COLUMN))
        {
            std::cout << "\tCommon ColumnDictionary  Negative Path Tests for Name to ID FAILED\n";
            return false;
        }
        std::cout << "\tAll Common ColumnDictionary Negative Path Tests Passed\n";
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "TestColumnDictionary::executeCommonGDTests() logic_error: " << le.what() << "\n\n";
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestColumnDictionary::executeCommonGDTests() UNEXPECTED EXCEPTION: " << e.what() << '\n';
        return false;
    }

    return allTestsPassed;
}

bool TestColumnDictionary::commonGDIdToName(ColumnDictionary &underTest, ColumnIds input, std::string expectedOutput) noexcept
{
    std::string actualOutPut = underTest.getNames(input);

    if (!expectedOutput.compare(actualOutPut) == 0)
    {
        std::cerr << "Common Dictionary Column ID to Name Test Failed " << expectedOutput << "\n";
        return false;
    }

    return true;
}

bool TestColumnDictionary::commonGDNameToID(ColumnDictionary &underTest, std::string input, ColumnIds expectedOutput) noexcept
{
    ColumnIds actualOutPut = underTest.getIds(input);

    if (expectedOutput != actualOutPut)
    {
        std::cerr << "\tColumn Name to ID Test Failed " << input << "\n";
        return false;
    }

    return true;
}

bool TestColumnDictionary::standAloneIdToName(ColumnIds input, std::string expectedOutput) noexcept
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
        std::cerr << "TestColumnDictionary::standAloneIdToName() logic_error: " << le.what() << "\n\n";
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestColumnDictionary::standAloneIdToName() UNEXPECTED EXCEPTION: " << e.what() << '\n';
        return false;
    }
    
    return true;
}

bool TestColumnDictionary::standAloneNameToID(std::string input, ColumnIds expectedOutput) noexcept
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
        std::cerr << "TestColumnDictionary::standAloneNameToID() logic_error: " << le.what() << "\n\n";
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestColumnDictionary::standAloneNameToID() UNEXPECTED EXCEPTION: " << e.what() << '\n';
        return false;
    }    

    return true;
}
