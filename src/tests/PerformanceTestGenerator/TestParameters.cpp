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
: progName{simplify_name(argv[0])},
  version{"2.0.0"},
  args{argv + 1, argv + argc}
{
    /*
     * common parts of help messages.
     */
    const std::string countMsg("test count: The number of tests to generate, ");
    const std::string sizeMsg("test size: The number of enum values in this test to generate, ");
    const std::string outPutFileMsg("The name of the output file to be generated");

/*
 * List the preferred longer flags first. This will make error messages easier to build.
 */
    testInfo = 
    {
        {"--output-file", ArgTypes::OutPutFile, outPutFileMsg, {0, 0}, 1},
        {"--test-count", ArgTypes::TestCount, countMsg, countRange, 1},
        {"--test-size", ArgTypes::TestSize, sizeMsg, sizeRange, 1},
        {"-c", ArgTypes::TestCount, countMsg, countRange, 2},
        {"-s", ArgTypes::TestSize, sizeMsg, sizeRange, 2},
        {"-f", ArgTypes::OutPutFile, outPutFileMsg, {0, 0}, 2},
        {"--help", ArgTypes::Help, "Print this help message.", {0, 0}, 2}
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

    printArgList();
    printMoreUsageInfo();

}

void TestParameters::printArgList() const noexcept
{
    for (auto tad: testInfo)
    {
        /*
         * Work around for the fact that g++-13 can't be installed on Ubuntu 22.04
         * so std::format() is not supported.
         */
        std::string legalValues("");
        if (tad.range.min > 0)
        {
            legalValues = "integer value between " + std::to_string(tad.range.min) +
                " and " + std::to_string(tad.range.max);
        }
        std::cerr << tad.argName << ":" << std::string(tad.tabCount, '\t') <<
            tad.helpMessage << legalValues << "\n";
    }
}

void TestParameters::printMoreUsageInfo() const noexcept
{
    std::cerr << "\nBy default the output of the program goes to the screen. The user can over ride this\n";
    std::cerr << "by either redirecting the output to a file or specifying the output file with the\n";
    std::cerr << "--output-file flag. If the user doesn't provide any arguments on the command line\n";
    std::cerr << "the program will request the number of tests and the test sizes\n";
}

void TestParameters::getUserInput() noexcept
{
    std::size_t testCount = 
        safeUserNumericInput("Enter the number of tests to generate",  countRange);

    for (std::size_t lcount = 0; lcount < testCount; ++lcount)
    {
        testValues.push_back(
            safeUserNumericInput("Enter the number of enums to generate for this test", sizeRange)
        );
    }
}

std::size_t TestParameters::safeUserNumericInput(std::string message, TestRange testRange)
{
    std::size_t safeNumber = 0;
    std::string safeInput;

    do {
        std::cout << message << " [" << testRange.min << "," << testRange.max << "]\n>>";
        std::cin >> safeInput;
        safeNumber = safeNumericConversion(safeInput, testRange);
    } while (safeNumber < 1);

    return safeNumber;
}

std::size_t TestParameters::safeNumericConversion(std::string userInput, TestRange testRange)
{
    try
    {
        std::size_t safeNumber = static_cast<std::size_t>(std::stoi(userInput, nullptr, 16));
        return ((safeNumber >= testRange.min && safeNumber <= testRange.max)? safeNumber : 0);
    }
    catch(std::invalid_argument& e)
    {
        return 0;
    }
    catch (std::out_of_range& e)
    {
        return 0;
    }
}

bool TestParameters::hasRequiredArgument(std::size_t currentArg, ArgTypes argType) noexcept
{
    if (currentArg >= args.size() || args[currentArg][0] == '-') 
    {
        std::cerr << "Missing required " << buildErrorMessageFromArg(argType) << "\n\n";
        usage();
        return false;
    }

    return true;
}

bool TestParameters::processTestSize(std::size_t currentArg) noexcept
{
    std::size_t input = processNumericArg(currentArg, ArgTypes::TestSize, sizeRange);
    if (input >= sizeRange.min)
    {
        testValues.push_back(input);
        return true;
    }

    return false;
}

std::size_t TestParameters::processNumericArg(std::size_t currentArg, ArgTypes argType, TestRange argRange) noexcept
{
    std::size_t input = 0;

    if (hasRequiredArgument(currentArg, argType))
    {
        input = safeNumericConversion(args[currentArg], argRange);
        if (input > argRange.min)
        {
            return input;
        }
        else
        {
            std::cerr << "Error in command line: " << buildArgsString(argType) <<" value " <<
                args[currentArg] << " out of range[" << argRange.min << "," << argRange.max << "]\n\n";
            usage();
        }
    }

    return 0;
}

bool TestParameters::processTestCount(std::size_t currentArg) noexcept
{
    testCount = processNumericArg(currentArg, ArgTypes::TestCount, countRange);

    return testCount >= countRange.min;
}

bool TestParameters::processOutputFile(std::size_t currentArg) noexcept
{
    if (hasRequiredArgument(currentArg, ArgTypes::OutPutFile))
    {
        outPutFile = args[currentArg];
        useCout = false;
        return true;
    }

    return false;
}

TestParameters::TestArgData TestParameters::getArgType(std::string flagStr) noexcept
{
    auto argData = std::find_if(testInfo.begin(), testInfo.end(),
        [&flagStr](TestArgData &flagData) {return (flagData.argName == flagStr);});

    return (argData != testInfo.end()? *argData : TestArgData{"error", ArgTypes::ErrorArgType, "Unknown switch", 0, 0, 0});
}

std::vector<std::string> TestParameters::getAllFlagNamesForErrorMessage(ArgTypes argType) noexcept
{
    std::vector<std::string> allArgNames;

    for (auto ti: testInfo)
    {
        if (ti.argType == argType)
        {
            allArgNames.push_back(ti.argName);
        }
    }

    return allArgNames;
}

/*
 * Assumes argType is a type that requires a second argument.
 */
std::string TestParameters::getTypeNameFromArg(ArgTypes argType) noexcept
{
    if (argType == ArgTypes::OutPutFile)
    {
        return "output file name";
    }

    return "integer value";
}

std::string TestParameters::buildErrorMessageFromArg(ArgTypes argType) noexcept
{
    std::string errorMessage(getTypeNameFromArg(argType));
    errorMessage += " for ";
    errorMessage += buildArgsString(argType);

    return errorMessage;
}

std::string TestParameters::buildArgsString(ArgTypes argType) noexcept
{
    std::string argsString;
    std::vector<std::string> argNames = getAllFlagNamesForErrorMessage(argType);
    bool useBrackets = false;

    for (auto argName: argNames)
    {
        argsString += useBrackets? " [" + argName + "]" : argName;
        useBrackets = true;
    }

    return argsString;
}
