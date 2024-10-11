#include <algorithm>
#include "TestParameters.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

static std::string simplify_name(char *path)
{
	return std::filesystem::path{path ? path : "createPerformanceTest"}.filename().string();
}

TestParameters::TestParameters(int argc, char *argv[])
: version{"2.0.0"},
  args{argv + 1, argv + argc}
{
    progName = simplify_name(argv[0]);
    testInfo = 
    {
        {"--output-file FILENAME", ArgTypes::OutPutFile, "The name of the output file to be generated"},
        {"--test-count INTEGER", ArgTypes::TestCount, "\ttest count: integer value between 1 and 10, the number of tests to generate"},
        {"--test-size INTEGER", ArgTypes::TestSize, "\ttest size: integer value between 1 and 524288 The number of enum values in this test to generat"},
        {"-c INTEGER", ArgTypes::TestCount, "\t\ttest count: integer value between 1 and 10, the number of tests to generate"},
        {"-s INTEGER", ArgTypes::TestSize, "\t\ttest size: integer value between 1 and 524288 The number of enum values in this test to generate"},
        {"-f FILENAME", ArgTypes::OutPutFile, "\t\tThe name of the output file to be generated"},
        {"--help", ArgTypes::Help, "\t\tPrint this help message."}
    };
}

bool TestParameters::getTestParameters() noexcept
{
    if (!processArguments())
    {
        return false;
    }

    if (testValues.size() == 0)
    {
        getUserInput();
    }

    return verifyTestCount();
}

bool TestParameters::verifyTestCount() const noexcept
{
    if (testCount > 0 && testCount != testValues.size())
    {
        std::cerr << "--test-count value (" << std::to_string(testCount) <<
            ") does not agree with number of test sizes input (" <<
            std::to_string(testValues.size()) << ")\n\n\n";
        usage();
        return false;
    }

    return true;
}

void TestParameters::usage() const noexcept
{
    std::cerr << progName << " " << version << "\n";
    std::cerr << "Usage: " << progName <<
        " [ [--output-file FILENAME] --test-count INTEGER --test-size INTEGER"
        " [--test-size INTEGER]*]\n";
    for (auto tad: testInfo)
    {
        std::cerr << tad.argName << ": " << tad.helpMessage << "\n";
    }

    std::cerr << "\nBy default the output of the program goes to the screen. The user can over ride this\n";
    std::cerr << "by either redirecting the output to a file or specifying the output file with the\n";
    std::cerr << "--output-file flag. If the user doesn't provide any arguments on the command line\n";
    std::cerr << "the program will request the number of tests and the test sizes\n";
}

void TestParameters::getUserInput() noexcept
{
    std::size_t testCount = 
        safeUserNumericInput("Enter the number of tests to generate", MIN_TEST_COUNT, MAX_TEST_COUNT);

    for (std::size_t lcount = 0; lcount < testCount; ++lcount)
    {
        testValues.push_back(
            safeUserNumericInput("Enter the number of enums to generate for this test", MIN_TEST_VALUE, MAX_TEST_VALUE)
        );
    }
}

std::size_t TestParameters::safeUserNumericInput(std::string message, std::size_t minValue, std::size_t maxValue)
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

bool TestParameters::is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

std::size_t TestParameters::safeNumericConversion(std::string userInput, std::size_t minValue, std::size_t maxValue)
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

bool TestParameters::hasRequiredArgument(std::size_t currentArg, std::string argName, std::string argType) const noexcept
{
    if (currentArg >= args.size() || args[currentArg][0] == '-') 
    {
        std::cerr << "Missing required " << argType << " for " << argName << "\n\n";
        usage();
        return false;
    }

    return true;
}

bool TestParameters::processArguments() noexcept
{
    // because some flags have an argument, old style C processing is used
    // to parse the flags and arguments.
    for (std::size_t currentArg = 0; currentArg < args.size(); ++currentArg)
    {
        if (args[currentArg][0] == '-')
        {
            auto testDatum = getArgType(args[currentArg]);
            switch (testDatum.argType)
            {
                default:
                    std::cerr << "Unknown switch " << args[currentArg] << " in command line\n";
                    usage();
                    return false;
                case ArgTypes::Help:
                    usage();
                    return false;
            // The following flags are followed by a required argument
                case ArgTypes::TestCount :
                    ++currentArg;
                    if (!processTestCount(currentArg))
                    {
                        usage();
                        return false;
                    }
                    break;
                case ArgTypes::TestSize :
                    ++currentArg;
                    if (!processTestSize(currentArg))
                    {
                        return false;
                    }
                    break;
                case ArgTypes::OutPutFile :
                    ++currentArg;
                    if (!processOutputFile(currentArg))
                    {
                        return false;
                    }
                    break;
            }
        }
    }

    return true;
}

// Need to find a way to use one function for processTestSize and processTestCount
bool TestParameters::processTestSize(std::size_t currentArg) noexcept
{
    if (hasRequiredArgument(currentArg, "--test-size [-s]", "integer value"))
    {
        std::size_t input = safeNumericConversion(args[currentArg], MIN_TEST_VALUE, MAX_TEST_VALUE);
        if (input > MIN_TEST_VALUE)
        {
            testValues.push_back(input);
            return true;
        }
        else
        {
            std::cerr << "Error in command line: --test-size [-s] value " <<
                args[currentArg] << " out of range[" << MIN_TEST_VALUE << "," << MAX_TEST_VALUE << "]\n\n";
            usage();
        }
    }

    return false;
}

bool TestParameters::processOutputFile(std::size_t currentArg) noexcept
{
    if (hasRequiredArgument(currentArg, "--output-file [-s]", "output file name"))
    {
        outPutFile = args[currentArg];
        useCout = false;
        return true;
    }

    return false;
}

bool TestParameters::processTestCount(std::size_t currentArg) noexcept
{
    if (hasRequiredArgument(currentArg, "---test-count [-c]", "integer value"))
    {
        std::size_t input = safeNumericConversion(args[currentArg], MIN_TEST_COUNT, MAX_TEST_COUNT);
        if (input > MIN_TEST_COUNT)
        {
            testCount = input;
            return true;
        }
        else
        {
            std::cerr << "Error in command line: --test-count [-c] value " <<
                args[currentArg] << " out of range[" << MIN_TEST_COUNT << "," << MAX_TEST_COUNT << "]\n\n";
            usage();
        }
    }

    return false;}

TestParameters::TestArgData TestParameters::getArgType(std::string flagStr) noexcept
{
    auto argData = std::find_if(testInfo.begin(), testInfo.end(),
        [&flagStr](TestArgData &flagData) {return (flagData.argName == flagStr);});

    return (argData != testInfo.end()? *argData : TestArgData{"error", ArgTypes::ErrorArgType, "Unknown switch"});
}
