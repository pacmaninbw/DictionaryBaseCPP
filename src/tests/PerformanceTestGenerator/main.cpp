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
    Help,
    ErrorArgType
};
struct TestArgData
{
    std::string argName;
    ArgTypes argType;
    std::string helpMessage;
};

static std::vector<TestArgData> testInfo =
{
    {"-c", ArgTypes::TestCount, "-c integer value between 1 and 10, the number of tests to generate"},
    {"--test-count", ArgTypes::TestCount, "--test-count integer value between 1 and 10, the number of tests to generate"},
    {"-s", ArgTypes::TestSize, "-c integer value between 1 and 10 The number of enum values in this test to generate"},
    {"--test-size", ArgTypes::TestSize, "The number of enum values in this test to generate"},
    {"-f", ArgTypes::OutPutFile, "The name of the output file to be generated"},
    {"--output-file", ArgTypes::OutPutFile, "The name of the output file to be generated"},
    {"--help", ArgTypes::Help, "Print this help message."}
};

static TestArgData getArgType(std::string flagStr) noexcept
{
    auto argData = std::find_if(testInfo.begin(), testInfo.end(),
        [&flagStr](TestArgData &flagData) {return (flagData.argName == flagStr);});

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

static void usage(TestParameters& testParameters)
{
    std::cerr << testParameters.progName << " " << testParameters.version << "\n";
    for (auto tad: testInfo)
    {
        std::cerr << tad.argName << ": " << tad.helpMessage << "\n";
    }
}

static bool processTestCount(std::vector<std::string> args, std::size_t currentArg, std::size_t& testCount)
{
    if (!(currentArg < args.size()) || args[currentArg][0] == '-')
    {
        std::cerr << "Missing integer value for --test-size\n\n";
        return false;
    }

    std::size_t input = safeNumericConversion(args[currentArg], MIN_TEST_COUNT, MAX_TEST_COUNT);
    if (input > MIN_TEST_COUNT)
    {
        testCount = input;
        return true;
    }

    return false;
}

static bool processTestSize(std::vector<std::string> args, std::size_t currentArg, TestParameters& testParameters)
{
    if (!(currentArg < args.size()) || args[currentArg][0] == '-')
    {
        std::cerr << "Missing integer value for --test-size\n\n";
        usage(testParameters);
        return false;
    }

    std::size_t input = safeNumericConversion(args[currentArg], MIN_TEST_VALUE, MAX_TEST_VALUE);
    if (input > MIN_TEST_VALUE)
    {
        testParameters.testValues.push_back(input);
        return true;
    }

    return false;
}

static bool processOutputFile(std::vector<std::string> args, std::size_t currentArg, TestParameters& testParameters)
{
    if (!(currentArg < args.size()) || args[currentArg][0] == '-')
    {
        std::cerr << "Missing output filename for --output-file\n\n";
        usage(testParameters);
        return false;
    }

    testParameters.outPutFile = args[currentArg];
    testParameters.useCout = false;
    return true;
}

static bool verifyTestCount(std::size_t testCount, TestParameters& testParameters)
{
    if (testCount > 0 && testCount != testParameters.testValues.size())
    {
        std::cerr << "--test-count value (" << std::to_string(testCount) <<
            ") does not agree with number of test sizes input (" <<
            std::to_string(testParameters.testValues.size()) << ")\n\n\n";
        usage(testParameters);
        return false;
    }

    return true;
}

static bool processArguments(std::vector<std::string> args, TestParameters& testParameters, std::size_t& testCount)
{
    for (std::size_t currentArg = 0; currentArg < args.size(); ++currentArg)
    {
        if (args[currentArg][0] == '-')
        {
            auto testDatum = getArgType(args[currentArg]);
            switch (testDatum.argType)
            {
                default:
                    std::cerr << "Unknown switch " << args[currentArg] << " in command line\n";
                    usage(testParameters);
                    return false;
                case ArgTypes::Help:
                    usage(testParameters);
                    return false;
            // The following flags are followed by a required argument
                case ArgTypes::TestCount :
                    ++currentArg;
                    if (!processTestCount(args, currentArg, testCount))
                    {
                        usage(testParameters);
                        return false;
                    }
                    break;
                case ArgTypes::TestSize :
                    ++currentArg;
                    if (!processTestSize(args, currentArg, testParameters))
                    {
                        return false;
                    }
                    break;
                case ArgTypes::OutPutFile :
                    ++currentArg;
                    if (!processOutputFile(args, currentArg, testParameters))
                    {
                        return false;
                    }
                    break;
            }
        }
    }

    return true;
}

static bool getTestParameters(int argc, char* argv[], TestParameters& testParameters)
{
    std::vector<std::string> args = {argv + 1, argv + argc};
    testParameters.progName = simplify_name(argv[0]);
    std::size_t testCount = 0;

    if (!processArguments(args, testParameters, testCount))
    {
        return false;
    }

    if (testParameters.testValues.size() == 0)
    {
        testParameters.testValues = getUserInput();
    }

    return verifyTestCount(testCount, testParameters);
}

int main(int argc, char* argv[])
{
    int exitStatus = EXIT_SUCCESS;

    TestParameters testParameters;
    testParameters.version = "2.0.0";

    exitStatus = getTestParameters(argc, argv, testParameters)? EXIT_SUCCESS: EXIT_FAILURE;

    if (exitStatus == EXIT_SUCCESS)
    {
        PerformanceTestGenerator generator(testParameters);
        exitStatus = generator.generateAllPerformaneTests()? EXIT_SUCCESS: EXIT_FAILURE;
    }

    return exitStatus;    
}
