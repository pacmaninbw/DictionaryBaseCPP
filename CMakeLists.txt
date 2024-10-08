cmake_minimum_required(VERSION 3.5)

project(TestDictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestDictionary
    src/tests/TestDictionary.cpp
    src/tests/ColumnDictionary.cpp
    src/tests/TableDictionary.cpp
    src/tests/TestColumnDictionary.cpp
    src/tests/TestTableDictionary.cpp
    src/tests/TestGenericDictionary.cpp
    )

target_compile_features(TestDictionary PUBLIC cxx_std_20)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # warning level 4 and all warnings as errors
    target_compile_options(TestTableMap PRIVATE /W4 /WX -D_CRT_SECURE_NO_WARNINGS)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # require at least gcc 12 to get full C++20 support
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
            message(FATAL_ERROR "GCC version must be at least 12!")
        endif()
    endif()
    # lots of warnings and all warnings as errors
    target_compile_options(TestDictionary PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
