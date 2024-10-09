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


    const std::size_t MinEnumVal = 1;
    const char* enumTemplate{"GD_PERFORMANCE_TEST_VALUE_"};
    const char* enumName{"GDPerformanceTestEnum"};
    const char* testStrTemplate{"Performance Test String "};
    const char* testStrVectorName{"GDPerformanceTestStrings"};
    std::vector<std::size_t> testValues;
    std::string progName;
    std::string version;
    bool useCout = true;
    std::string outPutFileName;
    std::ofstream outPutFile;
    std::streambuf* stdCoutBuffBackup = nullptr;
};

#endif // PERFORMANCETESTGENERATOR_H_
