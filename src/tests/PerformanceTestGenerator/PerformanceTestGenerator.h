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
    void dataPairLineOut(std::size_t lineC, std::string tabPlusOpen, bool lastLine) const noexcept;
    bool genTestDataPairs(std::size_t testSize, std::size_t tabCount) const noexcept;
    bool genTestDataPairsTable(std::size_t testSize) const noexcept;
    std::string genTestFunc(std::size_t testSize, bool useVector) const noexcept;
    bool generateAllTestDataAndTest(std::size_t testSize) noexcept;
    bool genPerformanceTest() noexcept;
    bool generateEnumValues(std::size_t testSize) const noexcept;
    bool generateEnum(std::size_t testSize) const noexcept;
    std::string reconstructCommandLine() noexcept;


    /*
     * The first 5 constants are used for enumeration code generation. While C++ enums
     * start at zero, the GenericDictionary class assumes that an enum with the value
     * of zero is an invalid, valid enums values are 1 through test size.
     *
     * GD stands for GenericDicionary
     */
    const std::size_t MinEnumVal = 1;
    const char* enumTemplate{"GD_PerfTestEnumValue_"};
    const char* enumName{"GDPerformanceTestEnum"};
    const char* firstEnum{"GD_Perf_Test_Invalid_enum_Value"};
    const char* lastEnum{"GD_Perf_Test_Last_Enum"};
    const char* testDataName{"testData"};
/*
 * The following constant are for testing the strings associated with the enums.
 */
    const char* testStrTemplate{"GD Perf Test String "};
//    const char* testStrVectorName{"GDPerformanceTestStrings"};

/*
 * Private variables
 */
    std::vector<std::size_t> testValues;    // Each item in in the vector is a test size to generate.
    std::string progName;
    std::string version;
    std::vector<std::string> testNames;
    bool useCout = true;
    std::string outPutFileName;
    std::ofstream outPutFile;
    std::streambuf* stdCoutBuffBackup = nullptr;
};

#endif // PERFORMANCETESTGENERATOR_H_
