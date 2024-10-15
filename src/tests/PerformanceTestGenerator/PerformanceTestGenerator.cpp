#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../UtilityTimer.h"
#include "PerformanceTestGenerator.h"

PerformanceTestGenerator::PerformanceTestGenerator(TestParameters testParameters)
 : testValues{testParameters.testValues},
    progName{testParameters.progName},
    version{testParameters.version},
    useCout{testParameters.useCout}
{
    if (!testParameters.useCout)
    {
        stdCoutBuffBackup = std::cout.rdbuf();
        outPutFileName = testParameters.outPutFile;
        outPutFile.open(outPutFileName);
        std::cout.rdbuf(outPutFile.rdbuf());
    }
}

PerformanceTestGenerator::~PerformanceTestGenerator()
{
    if (!useCout)
    {
        std::cout.rdbuf(stdCoutBuffBackup);
        outPutFile.close();
    }
}

bool PerformanceTestGenerator::generateAllPerformaneTests() noexcept
{
    std::cout << "#ifndef GD_PERFORMANCETEST_H_\n";
    std::cout << "#define GD_PERFORMANCETEST_H_\n\n";
    std::cout << "// Warning, this file is generated by a test generator " << progName << " " << version << "\n";
    std::cout << "// This file contains " << testValues.size() << " performance tests\n";
    std::cout << "// ";
    for (auto testEnumCount: testValues)
    {
        std::cout << " test " << testEnumCount << " enum values";
    }
    std::cout << "\n// The command line to reproduce this file is \n";
    std::cout << "//     " << reconstructCommandLine();
    std::cout << "\n\n";
    std::cout << "#include \"../../include/GenericDictionary.h\"\n";
    std::cout << "#include \"../BasicGenericDictionaryTests.h\"\n";
    std::cout << "#include <string>\n";
    std::cout << "#include \"../UtilityTimer.h\"\n";
    std::cout << "#include <vector>\n\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    if (!genPerformanceTest())
    {
        return false;
    }

    std::cout << "#endif // GD_PERFORMANCETEST_H_\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

bool PerformanceTestGenerator::generateEnumValues(std::size_t testSize) const noexcept
{
    for (std::size_t lcount = MinEnumVal; lcount <= testSize; ++lcount)
    {
        std::cout << "\t" << enumTemplate << lcount << ",\n";
    }

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

bool PerformanceTestGenerator::generateEnum(std::size_t testSize) const noexcept
{
    std::cout << "enum class " << enumName << testSize << "\n";
    std::cout << "{\n\t" << firstEnum <<",\n";

    if (!generateEnumValues(testSize))
    {
        return false;
    }

    std::cout << "\t" << lastEnum << "\n};\n";
    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

std::string PerformanceTestGenerator::reconstructCommandLine() noexcept
{
    std::string cmdLine(progName);

    cmdLine += ' ';

    if (!useCout)
    {
        cmdLine += "--output-file " + outPutFileName + ' ';
    }

    cmdLine += "--test-count " + std::to_string(testValues.size()) + ' ';
    for (auto testSize: testValues)
    {
        cmdLine += "--test-size " + std::to_string(testSize) + ' ';
    }

    return cmdLine;
}

void PerformanceTestGenerator::dataPairLineOut(std::size_t lineC, std::string tabPlusOpen, bool lastLine) const noexcept
{
    std::cout << tabPlusOpen << lineC << ", \"" << testStrTemplate << lineC << "\"}";
    
    if (!lastLine)
    {
        std::cout << ",";
    }

    std::cout << "\n";
}

bool PerformanceTestGenerator::genTestDataPairs(std::size_t testSize, std::size_t tabCount = 1) const noexcept
{
    std::string tSize(std::to_string(testSize));
    std::string enumValue(enumName + std::to_string(testSize) + "::" + enumTemplate);
    auto tabPlusOpen = std::string(tabCount, '\t') + '{' + enumValue;

    std::size_t lcount = MinEnumVal;
    for (; lcount < testSize ; ++lcount)
    {
        dataPairLineOut(lcount, tabPlusOpen, false);
    }
    dataPairLineOut(lcount, tabPlusOpen, true);

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

bool PerformanceTestGenerator::genTestDataPairsTable(std::size_t testSize) const noexcept
{
    std::string tpVecName("testData");
    tpVecName += std::to_string(testSize);

    std::cout << "\nstatic std::vector<TestPairs<" << enumName + std::to_string(testSize) <<
        ">> " << tpVecName << " =\n{\n";
    if (!genTestDataPairs(testSize))
    {
        return false;
    }
    std::cout << "};\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

std::string PerformanceTestGenerator::genTestFunc(std::size_t testSize) const noexcept
{
    std::string enumBase(enumName + std::to_string(testSize));
    std::string testName("performanceTest" + std::to_string(testSize));

    std::cout << "static bool " << testName << "()\n{\n" <<
        "\tbool testPassed = true;\n\tUtilityTimer testTimer;\n\n\tstd::string testName(\"" <<
        testName <<"\");\n\n\ttry {\n" <<
        "\t\tstd::clog << \"Testing GenericDictionary with enum of size " << testSize << "\\n\";" <<
        "\n\t\ttestTimer.startTimer();" <<
        "\n\t\tGenericDictionary <" << enumBase  << ", std::string> underTest (\n";

    enumBase += "::";

    std::cout << "\t\t\t" << enumBase << firstEnum << ",\n"
        "\t\t\t" << enumBase << lastEnum << ",\n\t\t\t{\n";

    if (!genTestDataPairs(testSize, 4))
    {
        return "";
    }

    std::cout << "\t\t\t}\n\t\t);\n\t\ttestTimer.stopTimerAndReport(\"Performance Test Constructor \" + testName + \" \");\n\n\t\t" <<
        "testPassed = performanceExecution<" << enumName + std::to_string(testSize)  <<
        ">(underTest, testData" << testSize << ", testName);\n"
        "\n\t}\n"
        "\tcatch (const std::logic_error &le)\n\t{\n"
        "\t\tstd::cerr << \"TestGenericDictionary::testContructorPositivePath() logic_error: \" << le.what() << \"\\n\\n\";\n"
        "\t\ttestPassed = false;\n\t}\n"
        "\tcatch(const std::exception& e)\n\t{\n"
        "\t\tstd::cerr << \"TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: \" << e.what() << \"\\n\";\n"        
        "\t\ttestPassed = false;\n\t}\n";
    std::cout << "\tstd::clog << \"GenericDictionary Constructor " << testName <<
        " \" << (testPassed? \"PASSED\\n\\n\": \"FAILED\\n\\n\");\n\n"
        "\treturn testPassed;\n}\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return "";
    }

    return testName;
}

std::string PerformanceTestGenerator::generateAllTestDataAndTest(std::size_t testSize) const noexcept
{
    std::cout <<
        "// Generated GenericDictionary Performance Test Values for an enum class of "
        << testSize << " enum values\n\n";

    if (!generateEnum(testSize)) return "";

    std::cout << "\n";
    if (!genTestDataPairsTable(testSize)) return "";

    std::cout << "\n";
    return genTestFunc(testSize);
}

bool PerformanceTestGenerator::genPerformanceTest() const noexcept
{
    std::vector<std::string> testNames;

    for (auto testSize: testValues)
    {
        std::string testName(generateAllTestDataAndTest(testSize));
        if (testName.length() > 0)
        {
            testNames.push_back(testName);
        }
        else
        {
            return false;
        }
    }

    std::cout << "bool performancetests()\n{\n\tbool allTestsPassed = true;\n\n";
    for (auto test: testNames)
    {
        std::cout << "\tif (allTestsPassed)\n\t{\n\t\tallTestsPassed = " << test << "();\n\t}\n";
    }

    std::cout << "\n\treturn allTestsPassed;\n}\n\n";
    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

