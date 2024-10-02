#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../UtilityTimer.h"

static std::size_t MinEnumVal = 1;
static std::string enumTemplate("GD_PERFORMANCE_TEST_VALUE_");
static std::string enumName("GDPerformanceTestEnum");
static std::string testStrTemplate("Performance Test String ");
static std::string testStrVectorName("GDPerformanceTestStrings");

static void generateEnum(std::ofstream &testOut, std::size_t testSize)
{
    testOut << "typedef enum class " << enumName << testSize << "\n";
    testOut << "{\n\tGD_PERFORMANCE_TEST_INVALID_VALUE,\n";
    for (std::size_t lcount = MinEnumVal; lcount <= testSize; ++lcount)
    {
        testOut << "\t" << enumTemplate << lcount << ",\n";
    }
    testOut << "\tGD_PERFORMANCE_LAST_ENUM\n} " << enumName << testSize << ";\n";
}

static void generateStringVector(std::ofstream &testOut, std::size_t testSize)
{
    testOut << "static std::vector<std::string> " << testStrVectorName << testSize << " = \n{\n"
        "\t\"\", // For GD_PERFORMANCE_TEST_INVALID_VALUE\n";
    for (std::size_t lcount = MinEnumVal; lcount <= testSize; ++lcount)
    {
        testOut << "\t\"" << testStrTemplate << lcount << "\",\n";
    }
    testOut << "\t\"\" // For GD_PERFORMANCE_LAST_ENUM\n};\n";
}

static std::string genEnumPreVal(std::size_t testSize)
{
    std::string tSize(std::to_string(testSize));
    std::string preEnumValue(enumName);
    return (preEnumValue += tSize);
}

static void genTestDataPairs(std::ofstream &testOut, std::size_t testSize, std::size_t tabCount = 1)
{
    std::string tSize(std::to_string(testSize));
    std::string enumValue(genEnumPreVal(testSize));
    enumValue += "::" + enumTemplate;
    std::string strValue(testStrVectorName);
    strValue += tSize + "[";
    std::string tabPlusOpen;
    for (std::size_t tcount = 0; tcount < tabCount; ++tcount)
    {
        tabPlusOpen += "\t";
    }
    tabPlusOpen += "{";

    std::size_t lcount = MinEnumVal;
    for (; lcount < testSize ; ++lcount)
    {
        testOut << tabPlusOpen << enumValue << lcount << ", " << strValue <<
            lcount << "]},\n";
    }
    testOut << tabPlusOpen << enumValue << lcount << ", " << strValue <<
            lcount << "]}\n";
}

static void genTestDataStructVector(std::ofstream &testOut, std::size_t testSize)
{
    std::string tpVecName("testData");
    tpVecName += std::to_string(testSize);

    testOut << "\nstatic std::vector<struct TestPairs<" << genEnumPreVal(testSize) <<
        ">> " << tpVecName << " =\n{\n";
    genTestDataPairs(testOut, testSize);
    testOut << "};\n\n";
}

static std::string genTestFunc(std::ofstream &testOut, std::size_t testSize)
{
    std::string enumBase(genEnumPreVal(testSize));
    std::string testName("performanceTest");
    testName += std::to_string(testSize);

    testOut << "static bool " << testName << "()\n{\n" <<
        "\tbool testPassed = true;\n\tUtilityTimer testTimer;\n\n\tstd::string testName(\"" <<
        testName <<"\");\n\n\ttry {\n" <<
        "\t\tstd::clog << \"Testing GenericDictionary with enum of size " << testSize << "\\n\";" <<
        "\n\t\ttestTimer.startTimer();" <<
        "\n\t\tGenericDictionary <" << enumBase  << ", std::string> underTest (\n";
    enumBase += "::";
    testOut << "\t\t\t" << enumBase << "GD_PERFORMANCE_TEST_INVALID_VALUE,\n"
        "\t\t\t" << enumBase << "GD_PERFORMANCE_LAST_ENUM,\n\t\t\t{\n";
    genTestDataPairs(testOut, testSize, 4);
    testOut << "\t\t\t}\n\t\t);\n\t\ttestTimer.stopTimerAndReport(\"Performance Test Constructor \" + testName + \" \");\n\n\t\t" <<
        "testPassed = performanceExecution<" << genEnumPreVal(testSize) <<
        ">(underTest, testData" << testSize << ", testName);\n"
        "\n\t}\n"
        "\tcatch (const std::logic_error &le)\n\t{\n"
        "\t\tstd::cerr << \"TestGenericDictionary::testContructorPositivePath() logic_error: \" << le.what() << \"\\n\\n\";\n"
        "\t\ttestPassed = false;\n\t}\n"
        "\tcatch(const std::exception& e)\n\t{\n"
        "\t\tstd::cerr << \"TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: \" << e.what() << \"\\n\";\n"        
        "\t\ttestPassed = false;\n\t}\n";
    testOut << "\tstd::clog << \"GenericDictionary Constructor " << testName <<
        " \" << (testPassed? \"PASSED\\n\\n\": \"FAILED\\n\\n\");\n\n"
        "\treturn testPassed;\n}\n\n";

    return testName;
}


static std::string generateAllTestDataAndTest(std::ofstream &testOut, std::size_t testSize)
{
    testOut << "// Generated GenericDictionary Performance Test Values for an enum class of ";
    testOut << testSize << " enum values\n\n";

    generateEnum(testOut, testSize);

    testOut << "\n";
    generateStringVector(testOut, testSize);

    testOut << "\n";
    genTestDataStructVector(testOut, testSize);

    testOut << "\n";
    return genTestFunc(testOut, testSize);
}

static void genPerformanceTest(std::ofstream &testOut, std::vector<std::size_t> testValues)
{
    std::vector<std::string> testNames;
    for (auto test: testValues)
    {
        testNames.push_back(generateAllTestDataAndTest(testOut, test));
    }

    testOut << "bool performancetests()\n{\n\tbool allTestsPassed = true;\n\n";
    for (auto test: testNames)
    {
        testOut << "\tif (allTestsPassed)\n\t{\n\t\tallTestsPassed = " << test << "();\n\t}\n";
    }
    testOut << "\n\treturn allTestsPassed;\n}\n\n";
}

static bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

static std::size_t safeUserNumericInput(std::string message, std::size_t minValue, std::size_t maxValue)
{
    std::size_t safeNumber;

    std::string safeInput;
    bool hasNumber = false;

    do {
        std::cout << message << " [" << minValue << "," << maxValue << "]\n>>";
        std::cin >> safeInput;
        hasNumber = is_number(safeInput);
        if (hasNumber)
        {
            safeNumber = std::stoi(safeInput);
            hasNumber = (safeNumber >= minValue || safeNumber <= maxValue);
        }
    } while (!hasNumber);

    return safeNumber;
}

static std::vector<std::size_t> getUserInput()
{
    const std::size_t MIN_TEST_COUNT = 1;
    const std::size_t MAX_TEST_COUNT = 10;
    const std::size_t MIN_TEST_VALUE = 1;
    const std::size_t MAX_TEST_VALUE = (1024 * 1024 * 3);

    std::vector<std::size_t> testValues;

    std::size_t testCount = 
        safeUserNumericInput("Enter the number of tests to generate", MIN_TEST_COUNT, MAX_TEST_COUNT);
    for (std::size_t lcount = 0; lcount < testCount; ++lcount)
    {
        testValues.push_back(
            safeUserNumericInput("Enter the number of enums to generate for this test", MIN_TEST_VALUE, MAX_TEST_VALUE)
        );
    }

    return testValues;
}

int main(void)
{
    int exitStatus = EXIT_SUCCESS;

    std::ofstream testOut;
    testOut.open("performanceTest.h");

    std::vector<std::size_t> testValues = getUserInput();

    testOut << "#ifndef GD_PERFORMANCETEST_H_\n";
    testOut << "#define GD_PERFORMANCETEST_H_\n\n";
    testOut << "// Warning, this file is generated by a test generator\n";
    testOut << "// This file contains " << testValues.size() << " performance tests\n";
    testOut << "// ";
    for (auto testEnumCount: testValues)
    {
        testOut << " test " << testEnumCount << "enum values";
    }
    testOut << "\n\n";
    testOut << "#include \"../../include/GenericDictionary.h\"\n";
    testOut << "#include \"../BasicGenericDictionaryTests.h\"\n";
    testOut << "#include <string>\n";
    testOut << "#include \"../UtilityTimer.h\"\n";
    testOut << "#include <vector>\n\n\n";
    genPerformanceTest(testOut, testValues);
    testOut << "#endif // GD_PERFORMANCETEST_H_\n\n";

    testOut.close();

    return exitStatus;
}