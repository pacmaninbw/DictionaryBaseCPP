#include "TestParameters.h"
#include "PerformanceTestGenerator.h"
#include "../../include/UtilityTimer.h"

int main(int argc, char* argv[])
{
    int exitStatus = EXIT_SUCCESS;

    TestParameters testParameters(argc, argv);

    exitStatus = testParameters.getTestParameters()? EXIT_SUCCESS: EXIT_FAILURE;

    if (exitStatus == EXIT_SUCCESS)
    {
        PerformanceTestGenerator generator(testParameters);
        exitStatus = generator.generateAllPerformaneTests()? EXIT_SUCCESS: EXIT_FAILURE;
    }

    return exitStatus;    
}
