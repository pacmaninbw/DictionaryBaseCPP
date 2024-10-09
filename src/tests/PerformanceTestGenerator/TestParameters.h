#ifndef TESTPARAMETERS_H_
#define TESTPARAMETERS_H_

#include <string>
#include <vector>

struct TestParameters
{
    std::string progName;
    std::string version;
    std::vector<std::size_t> testValues;
    bool useCout = true;
    std::string outPutFile;
};

#endif // TESTPARAMETERS_H_