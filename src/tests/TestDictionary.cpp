#include <iostream>
#include "TestColumnDictionary.h"
#include "TestGenericDictionary.h"
#include "TestTableDictionary.h"

int main()
{
    int exitStatus = EXIT_SUCCESS;

    try
    {
        TestGenericDictionary genericDicionaryTest;
        TestColumnDictionary columnsDictionaryTest;
        TestTableDictionary tableDictionaryTest;

        if (!genericDicionaryTest.executeTests())
        {
            exitStatus = EXIT_FAILURE;
        }

        if (!columnsDictionaryTest.executeTests())
        {
            exitStatus = EXIT_FAILURE;
        }

        if (!tableDictionaryTest.executeTests())
        {
            exitStatus = EXIT_FAILURE;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exitStatus = EXIT_FAILURE;
    }

    std::cout << (exitStatus == EXIT_FAILURE ? "Tests Failed\n\n" : "All Tests Passed\n\n");

    return exitStatus;
}
