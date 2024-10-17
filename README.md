# C++ Generic Dictionary With Unit Test and Performance Tests  

The src/include/GenericDictionary.h contains a generic class for associating enums or integers (numeric constants) 
with strings or more complex mechanisms. It can be a base class for other converters.

The src/tests/TestDictionary.cpp file contains the unit testing for the GenericDictionary 
class as well as classes that inherit from the GenericDictionary base class.

The ColumnDictionary files and the TableDictionary files are from 
another project that uses the GenericDictionary class defined in
GenericDictionary.h.

The GenericDictionary expects enums of a particular format:

```
enum class ENUMNAME
{
	Invalid_enum_Value,
	EnumValue_1,
    ...
	EnumValue_N,
	Last_Enum
};
```

Strings can be assigned to EnumValue_1 through EnumValue_N.

The DictionaryBase class should be portable to all systems and all C++20 compilers.

# Development Environments
- C++ 20
- CMake
## Linux Development
- gcc 12
- Ubuntu 22.04
- Visual Studio Code (vscode)
## Windows Development
- Windows 10
- Visual Studion 2022

# Status
This code was reviewed on the [Stack Exchange Code Review site](https://codereview.stackexchange.com/questions/293782/generic-c-class-to-associate-enum-values-with-strings-for-translation). The code reviewed in that review can be found in the `PreCodeReview` branch. Development is continuing in the `master` branch.  

The [performance test generator code was also reviewed](https://codereview.stackexchange.com/questions/293933/c20-performance-test-code-generator) on the Stack Exchange Code Review site. The code reviewed by that review can be found in found in this [branch on GitHub](https://github.com/pacmaninbw/DictionaryBaseCPP/tree/PerformanceTestGeneratorCodeReview).

The master branch contains corrections from both code review.

# Todo Items
 - Add performance tests that test different containers in the GenericDictionary (std::vector versus std::map)
 - Integrate the generated performance tests into the unit testing.
