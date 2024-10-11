#ifndef PERFORMANCETESTGENERATOR_H_
#define PERFORMANCETESTGENERATOR_H_

#include "TestParameters.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class PerformanceTestGenerator {
public:
    PerformanceTestGenerator(TestParameters testParameters);
    ~PerformanceTestGenerator();
    bool generateAllPerformaneTests() noexcept;

private:
    bool genTestDataPairs(std::size_t testSize, std::size_t tabCount) const noexcept;
    bool genTestDataStructVector(std::size_t testSize) const noexcept;
    std::string genTestFunc(std::size_t testSize) const noexcept;
    std::string generateAllTestDataAndTest(std::size_t testSize) const noexcept;
    bool genPerformanceTest() const noexcept;
    bool generateEnum(std::size_t testSize) const noexcept;
    bool generateStringVector(std::size_t testSize) const noexcept;
    std::string reconstructCommandLine() noexcept;

/*
 * The first 3 constants are used for enumeration code generation. While C++ enums
 * start at zero, the GenericDictionary class assumes that an enum with the value
 * of zero is an invalid, valid enums values are 1 through test size.
 * 
 * GD stands for GenericDicionary
 */
    const std::size_t MinEnumVal = 1;
    const char* enumTemplate{"GD_PerfTestEnumValue_"};
    const char* enumName{"GDPerformanceTestEnum"};
/*
 * The following 2 constants are for testing the strings associated with the enums.
 */
    const char* testStrTemplate{"GD Perf Test String "};
    const char* testStrVectorName{"GDPerformanceTestStrings"};

/*
 * Private variables
 */
    std::vector<std::size_t> testValues;    // Each item in in the vector is a test size to generate.
    std::string progName;
    std::string version;
    bool useCout = true;
    std::string outPutFileName;
    std::ofstream outPutFile;
    std::streambuf* stdCoutBuffBackup = nullptr;
};

#endif // PERFORMANCETESTGENERATOR_H_
