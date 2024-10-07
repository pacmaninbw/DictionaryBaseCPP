#ifndef TESTPARAMETERS_H_
#define TESTPARAMETERS_H_

#include <string>
#include <vector>

struct TestParameters
{
    std::vector<std::size_t> testValues;
    std::string progName;
    bool useCout = true;
    std::string outPutFile;
};

#endif // TESTPARAMETERS_H_