# C++ Generic Dictionary With Unit Test and Performance Tests  

The src/include/GenericDictionary.h contains a generic class for associating enums or integers (numeric constants) 
with strings or more complex mechanisms. It can be a base class for 
other converters.

The src/tests/TestDictionary.cpp file contains the unit testing for the GenericDictionary 
class as well as classes that inherit from the GenericDictionary base class.

The ColumnDictionary files and the TableDictionary files are from 
another project that uses the GenericDictionary class defined in
GenericDictionary.h.

The DictionaryBase class should be portable to all systems and all C++20 compilers.

# Development Environment
- C++ 20
- CMake
- gcc 12
- Ubuntu 22.04
- Visual Studio Code (vscode)

# Status
This code was reviewed on the [Stack Exchange Code Review site](https://codereview.stackexchange.com/questions/293782/generic-c-class-to-associate-enum-values-with-strings-for-translation). The code reviewed in that review can be found in the `PreCodeReview` branch. Development is continuing in the `master` branch.  

# Todo Items
 - Add command line processing to the performance test generator
 - Add a comment in the generated performance test that contains the name of the test generator as well as the test generator arguments.
 - Add performance tests that test different containers in the GenericDictionary (std::vector versus std::map)
 - Integrate the generated performance tests into the unit testing.
