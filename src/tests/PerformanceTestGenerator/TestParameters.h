#ifndef TESTPARAMETERS_H_
#define TESTPARAMETERS_H_

#include <string>
#include <vector>

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
    bool verifyTestCount() const noexcept;
    void usage() const noexcept;
    void getUserInput() noexcept;
    std::size_t safeUserNumericInput(std::string message, std::size_t minValue, std::size_t maxValue);
    bool is_number(const std::string& s);
    std::size_t safeNumericConversion(std::string userInput, std::size_t minValue, std::size_t maxValue);
    bool hasRequiredArgument(std::size_t currentArg, std::string argName, std::string argType) const noexcept;
    bool processArguments() noexcept;
    bool processTestSize(std::size_t currentArg) noexcept;
    bool processOutputFile(std::size_t currentArg) noexcept;
    bool processTestCount(std::size_t currentArg) noexcept;


    std::vector<std::string> args;
    std::size_t testCount = 0;

    const std::size_t MIN_TEST_COUNT = 1;
    const std::size_t MAX_TEST_COUNT = 10;
    const std::size_t MIN_TEST_VALUE = 1;
    const std::size_t MAX_TEST_VALUE = (1024 * 512);

    enum class ArgTypes
    {
        TestSize,
        TestCount,
        OutPutFile,
        Help,
        ErrorArgType
    };
    struct TestArgData
    {
        std::string argName;
        ArgTypes argType;
        std::string helpMessage;
    };
    std::vector<TestArgData> testInfo;
    TestArgData getArgType(std::string flagStr) noexcept;
};

#endif // TESTPARAMETERS_H_