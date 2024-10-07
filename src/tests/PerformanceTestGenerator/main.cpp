#include <algorithm>
#include "TestParameters.h"
#include <filesystem>
#include <iostream>
#include "PerformanceTestGenerator.h"
#include <string>
#include <vector>
#include "../UtilityTimer.h"

static constexpr std::size_t MIN_TEST_COUNT = 1;
static constexpr std::size_t MAX_TEST_COUNT = 10;
static constexpr std::size_t MIN_TEST_VALUE = 1;
static constexpr std::size_t MAX_TEST_VALUE = (1024 * 512);


static bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

static std::size_t safeNumericConversion(std::string userInput, std::size_t minValue, std::size_t maxValue)
{
    if (is_number(userInput))
    {
        std::size_t safeNumber = std::stoi(userInput);
        if (safeNumber >= minValue || safeNumber <= maxValue)
        {
            return safeNumber;
        }
    }

    return 0;
}

enum class ArgTypes
{
    TestSize,
    TestCount,
    OutPutFile,
    ErrorArgType
};
struct TestArgData
{
    std::string argName;
    ArgTypes argType;
    std::string helpMessage;
};

static std::vector<struct TestArgData> testInfo =
{
    {"-c", ArgTypes::TestCount, "-c integer value between 1 and 10, the number of tests to generate"},
    {"--test-count", ArgTypes::TestCount, "--test-count integer value between 1 and 10, the number of tests to generate"},
    {"-s", ArgTypes::TestSize, "-c integer value between 1 and 10 The number of enum values in this test to generate"},
    {"--test-size", ArgTypes::TestSize, "The number of enum values in this test to generate"},
    {"-f", ArgTypes::OutPutFile, "The name of the output file to be generated"},
    {"--output-file", ArgTypes::OutPutFile, "The name of the output file to be generated"},
};

static struct TestArgData getArgType(std::string flagStr) noexcept
{
    auto argData = std::find_if(testInfo.begin(), testInfo.end(),
        [&flagStr](struct TestArgData &flagData) {return (flagData.argName == flagStr);});

    return (argData != testInfo.end()? *argData : TestArgData{"error", ArgTypes::ErrorArgType, "Unknown switch"});
}

static std::size_t safeUserNumericInput(std::string message, std::size_t minValue, std::size_t maxValue)
{
    std::size_t safeNumber = 0;
    std::string safeInput;

    do {
        std::cout << message << " [" << minValue << "," << maxValue << "]\n>>";
        std::cin >> safeInput;
        safeNumber = safeNumericConversion(safeInput, minValue, maxValue);
    } while (safeNumber < 1);

    return safeNumber;
}

static std::vector<std::size_t> getUserInput()
{

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

static std::string simplify_name(char *path)
{
	return std::filesystem::path{path ? path : "createPerformanceTest"}.filename().string();
}

static void usage()
{
    std::cerr << "Errors ocurred either processing the command line or during user input.";
}

static bool processTestCount(std::string userInput,  std::size_t& testCount)
{
    std::size_t input = safeNumericConversion(userInput, MIN_TEST_COUNT, MAX_TEST_COUNT);
    if (input > MIN_TEST_COUNT)
    {
        testCount = input;
        return true;
    }

    return false;
}

static bool processTestSize(std::string userInput, struct TestParameters& testParameters)
{
    std::size_t input = safeNumericConversion(userInput, MIN_TEST_VALUE, MAX_TEST_VALUE);
    if (input > MIN_TEST_VALUE)
    {
        testParameters.testValues.push_back(input);
        return true;
    }

    return false;
}

static bool processOutputFile(std::string userInput, struct TestParameters& testParameters)
{
    testParameters.outPutFile = userInput;
    testParameters.useCout = false;
    return true;
}

static bool getTestParameters(int argc, char* argv[], struct TestParameters& testParameters)
{
    std::vector<std::string> args = {argv + 1, argv + argc};
    testParameters.progName = simplify_name(argv[0]);
    std::size_t testCount = 0;

    for (int currentArg = 0; currentArg < argc - 1; ++currentArg)
    {
        if (args[currentArg][0] == '-')
        {
            auto testDatum = getArgType(args[currentArg]);
            switch (testDatum.argType)
            {
                case ArgTypes::TestCount :
                    processTestCount(args[++currentArg], testCount);
                    break;
                case ArgTypes::TestSize :
                    processTestSize(args[++currentArg], testParameters);
                    break;
                case ArgTypes::OutPutFile :
                    processOutputFile(args[++currentArg], testParameters);
                    break;
                default:
                    std::cerr << "Unknown switch " << args[currentArg] << " in command line\n";
                    return false;
            }
        }
    }

    if (testParameters.testValues.size() == 0)
    {
        testParameters.testValues = getUserInput();
    }

    if (testCount > 0 && testCount != testParameters.testValues.size())
    {
        usage();
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    int exitStatus = EXIT_SUCCESS;

    TestParameters testParameters;

    exitStatus = getTestParameters(argc, argv, testParameters)? EXIT_SUCCESS: EXIT_FAILURE;

    if (exitStatus == EXIT_SUCCESS)
    {
        PerformanceTestGenerator generator(testParameters);
        std::string cmdLine(simplify_name(argv[0]));
        cmdLine += ' ';
        for (int i = 1; i < argc; i++)
        {
            cmdLine += argv[i] + ' ';
        }
        exitStatus = generator.generateAllPerformaneTests()? EXIT_SUCCESS: EXIT_FAILURE;
    }

    return exitStatus;    
}
