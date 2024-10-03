#include "../PerformanceTestGenerator/performanceTest.h"

int main(void)
{
    if (!performancetests())
    {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

