# C++ Generic Dictionary With Unit Test  

AbstractDictionary.h contains a generic class for associating enums or integers 
with strings or more complex mechanisms. It is meant to be a base class for 
other converters.

The TestDictionary.cpp file contains the unit testing for the AbstractDictionary 
class as well as classes that inherit from the AbstractDictionary base class.

The ColumnDictionary files and the TableDictionary files are from 
another project that uses the DictionaryBase class defined in
AbstractDictionary.h.

The DictionaryBase class should be portable to all systems and all C++ compilers.

# Development Environment
- C++ 20
- CMake
- gcc 12
- Ubuntu 22.04
- Visual Studio Code (vscode)

# Status
This code was reviewed on the [Stack Exchange Code Review site](https://codereview.stackexchange.com/questions/293782/generic-c-class-to-associate-enum-values-with-strings-for-translation). The code reviewed in that review can be found in the `PreCodeReview` branch. Development is continuing in the `master` branch. 
