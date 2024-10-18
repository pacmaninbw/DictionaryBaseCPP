#define GD_PERFORMANCE_TEST
#include <exception>
#include "../include/GenericDictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include "TestGenericDictionary.h"
#include <vector>

TestGenericDictionary::TestGenericDictionary()
{

}

bool TestGenericDictionary::executeTests() noexcept
{
    bool allTestsPassed = true;
    UtilityTimer testTimer;

    std::cout << "Testing the GenericDictionary class\n";
    try
    {
        testTimer.startTimer();
        if (!testContructorPositivePath())
        {
            allTestsPassed = false;
        }
        testTimer.stopTimerAndReport("Positive Path Constructor Test ");

        testTimer.startTimer();
        if (!testConstructorMissingIDDef())
        {
            allTestsPassed = false;
        }
        testTimer.stopTimerAndReport("Negative Path Constructor Test: Missing ID Enum ");

        testTimer.startTimer();
        if (!testConstructorDuplicateID())
        {
            allTestsPassed = false;
        }
        testTimer.stopTimerAndReport("Negative Path Constructor Test: Duplicate ID Enum ");

        testTimer.startTimer();
        if (!testConstructorDuplicateName())
        {
            allTestsPassed = false;
        }
        testTimer.stopTimerAndReport("Negative Path Constructor Test: Duplicate Name string ");
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "TestGenericDictionary::executeTests() UNCAUGHT logic_error: " <<
            le.what() << "\n\n";
        return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestGenericDictionary::executeTests() UNCAUGHT UNKNOWN EXCEPTION: " <<
            e.what() << "\n\n";
        return false;
    }
    
    if (allTestsPassed)
    {
        std::cout << "Testing the GenericDictionary class: ALL TESTS PASSED!\n";
    }
    else
    {
        std::cerr << "Testing the GenericDictionary class: SOME OR ALL TESTS FAILED!\n";
    }

    return allTestsPassed;
}

/*
 * GD for GenericDictionary
 */
static std::vector<std::string> positiveGDTestStrings = 
{
    "", // For GDPOSITIVE_INVALID_VALUE
    "Test String 1", // For GDPOSITIVE_TEST_VALUE_1
    "Test String 2", // For GDPOSITIVE_TEST_VALUE_2
    "Test String 3", // For GDPOSITIVE_TEST_VALUE_3
    "Test String 4", // For GDPOSITIVE_TEST_VALUE_4
    "Test String 5", // For GDPOSITIVE_TEST_VALUE_5
    "Test String 6", // For GDPOSITIVE_TEST_VALUE_6
    "" // For GDPOSITIVE_LAST_ENUM
};

static std::vector<TestPairs<GDPositivePathEnum>> testData =
{
    {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_1, positiveGDTestStrings[1]},
    {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_2, positiveGDTestStrings[2]},
    {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_3, positiveGDTestStrings[3]},
    {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_4, positiveGDTestStrings[4]},
    {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_5, positiveGDTestStrings[5]},
    {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_6, positiveGDTestStrings[6]},
};

/*
 * Basic Positive Path test of the GenericDictionary class. If the constructor
 * does not throw an exception continue testing the default implementation of
 * the public methods.S
*/
bool TestGenericDictionary::testContructorPositivePath() noexcept
{
    bool testPassed = true;

    try
    {
        std::cout << "GenericDictionary Constructor Positive Path Test\n";

        GenericDictionary <GDPositivePathEnum, std::string> underTest(
            GDPositivePathEnum::GDPOSITIVE_INVALID_VALUE,
            GDPositivePathEnum::GDPOSITIVE_LAST_ENUM,
            {
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_1, positiveGDTestStrings[1]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_2, positiveGDTestStrings[2]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_3, positiveGDTestStrings[3]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_4, positiveGDTestStrings[4]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_5, positiveGDTestStrings[5]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_6, positiveGDTestStrings[6]}
            }
        );
        
        std::cout << "\tTest GenericDictionary Constructor Positive Path No exception thrown PASSED\n";
        if ((testPassed = testIDtoNameLoop<GDPositivePathEnum>(underTest, testData, "testContructorPositivePath::testIDtoNameLoop()")))
        {
            testPassed = testNametoIDLoop<GDPositivePathEnum>(underTest, testData,"testContructorPositivePath::testNametoIDLoop");
        }
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "TestGenericDictionary::testContructorPositivePath() logic_error: " <<
            le.what() << "\n\n";
        testPassed = false;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: " <<
            e.what() << "\n\n";
        testPassed = false;
    }
    
    std::cout << "GenericDictionary Constructor Positive Path Test " <<
        (testPassed? "PASSED\n\n": "FAILED\n\n");

    return testPassed;
}

/*
 * If the constructor is missing an ID definition, the constructor is expected
 * to throw a std::logic_error exception.
 */
bool TestGenericDictionary::testConstructorMissingIDDef() noexcept
{
    try
    {
        std::cout << "GenericDictionary Constructor Negative Path Test: Missing ID enum\n";
        
        // GDPOSITIVE_TEST_VALUE_3 removed from constructor
        GenericDictionary <GDPositivePathEnum, std::string> expectedFailure(
            GDPositivePathEnum::GDPOSITIVE_INVALID_VALUE,
            GDPositivePathEnum::GDPOSITIVE_LAST_ENUM,
            {
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_1, positiveGDTestStrings[1]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_2, positiveGDTestStrings[2]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_4, positiveGDTestStrings[4]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_5, positiveGDTestStrings[5]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_6, positiveGDTestStrings[6]}
            }
        );
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "GenericDictionary Constructor threw expected std::logic_error: " << le.what() << "\n";
        std::cout << "\tGenericDictionary Constructor Negative Path Test: Missing ID enum: PASSED\n\n";
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: " <<
            e.what() << "\n\n";
        return false;
    }
    
    std::cerr << "GenericDictionary Constructor Negative Path Test: Missing ID enum: FAILED\n\n";

    return false;
}

bool TestGenericDictionary::testConstructorDuplicateID() noexcept
{
    try
    {
        std::cout << "GenericDictionary Constructor Negative Path Test: Duplicate ID enum\n";
        
        // GDPOSITIVE_TEST_VALUE_2 is duplicated
        GenericDictionary <GDPositivePathEnum, std::string> expectedFailure(
            GDPositivePathEnum::GDPOSITIVE_INVALID_VALUE,
            GDPositivePathEnum::GDPOSITIVE_LAST_ENUM,
            {
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_1, positiveGDTestStrings[1]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_2, positiveGDTestStrings[2]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_3, positiveGDTestStrings[3]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_4, positiveGDTestStrings[4]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_2, positiveGDTestStrings[2]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_6, positiveGDTestStrings[6]}
            }
        );
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "GenericDictionary Constructor threw expected std::logic_error: " << le.what() << "\n";
        std::cout << "\tGenericDictionary Constructor Negative Path Test: Duplicate ID enum: PASSED\n\n";
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: " <<
            e.what() << "\n\n";
        return false;
    }
    
    std::cerr << "GenericDictionary Constructor Negative Path Test: Duplicate ID enum: FAILED\n\n";

    return false;
}

bool TestGenericDictionary::testConstructorDuplicateName() noexcept
{
    try
    {
        std::cout << "GenericDictionary Constructor Negative Path Test: Duplicate Name string\n";
        
        // positiveGDTestStrings[2] is duplicated
        GenericDictionary <GDPositivePathEnum, std::string> expectedFailure(
            GDPositivePathEnum::GDPOSITIVE_INVALID_VALUE,
            GDPositivePathEnum::GDPOSITIVE_LAST_ENUM,
            {
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_1, positiveGDTestStrings[1]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_2, positiveGDTestStrings[2]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_3, positiveGDTestStrings[3]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_4, positiveGDTestStrings[4]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_5, positiveGDTestStrings[2]},
                {GDPositivePathEnum::GDPOSITIVE_TEST_VALUE_6, positiveGDTestStrings[6]}
            }
        );
    }
    catch (const std::logic_error &le)
    {
        std::cerr << "GenericDictionary Constructor threw expected std::logic_error: " << le.what() << "\n";
        std::cout << "\tGenericDictionary Constructor Negative Path Test: Duplicate Name string: PASSED\n\n";
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: " <<
            e.what() << "\n\n";
        return false;
    }
    
    std::cerr << "GenericDictionary Constructor Negative Path Test: Duplicate Name string: FAILED\n\n";

    return false;
}



