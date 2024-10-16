#ifndef TESTPARAMETERS_H_
#define TESTPARAMETERS_H_

#include <string>
#include <utility>
#include <vector>

/*
 * Get the test generation parameters. For output the program defaults to
 * standard out. There are no defaults for the number of tests to generate
 * or the size of the tests to generate. If the user does not enter this
 * information on the command line the program will ask the user to provide
 * input.
 */
class TestParameters
{
public:
    TestParameters(int argc, char* argv[]);
    bool getTestParameters() noexcept;
    std::string progName;
    std::string version;
    std::vector<std::size_t> testValues;
    bool useCout = true;
    std::string outPutFile;

private:
    enum class ArgTypes
    {
        TestSize,
        TestCount,
        OutPutFile,
        Help,
        ErrorArgType
    };

    struct TestRange
    {
        std::size_t min;
        std::size_t max;
    };

    struct TestArgData
    {
        std::string argName;
        ArgTypes argType;
        std::string helpMessage;
        TestRange range;
        std::size_t tabCount;
    };

    bool verifyTestCount() const noexcept;
    void usage() const noexcept;
    void printArgList() const noexcept;
    void printMoreUsageInfo() const noexcept;
    void getUserInput() noexcept;
    void userInputFileName() noexcept;
    std::size_t safeUserNumericInput(std::string message, TestRange testRange);
    std::size_t safeNumericConversion(std::string userInput, TestRange testRange);
    bool hasRequiredArgument(std::size_t currentArg, ArgTypes argType) noexcept;
    bool processArguments() noexcept;
    bool processOutputFile(std::size_t currentArg) noexcept;
    bool processTestCount(std::size_t currentArg) noexcept;
    bool processTestSize(std::size_t currentArg) noexcept;
    std::size_t processNumericArg(std::size_t currentArg, ArgTypes argType, TestRange argRange) noexcept;
    TestArgData getArgType(std::string flagStr) noexcept;
    std::vector<std::string> getAllFlagNamesForErrorMessage(ArgTypes argType) noexcept;
    std::string getTypeNameFromArg(ArgTypes argType) noexcept;
    std::string buildErrorMessageFromArg(ArgTypes argType) noexcept;
    std::string buildArgsString(ArgTypes argType) noexcept;

/*
 * These constant are used for error checking during user input or
 * command line parsing. The numbers are somewhat arbitrary. Due to
 * the limitations of the compilers on the development machine the
 * maximum test size is limited to 512K.
 */
    const std::size_t MinTestCount = 1;
    const std::size_t MaxTestCount = 10;
    const std::size_t MinTestSize = 1;
    const std::size_t MaxTestSize = (1024 * 512); // 512K

    const TestRange sizeRange{MinTestSize, MaxTestSize};
    const TestRange countRange{MinTestCount, MaxTestCount};

    std::vector<std::string> args;
    std::size_t testCount = 0;
    std::vector<TestArgData> testInfo;
};

#endif // TESTPARAMETERS_H_