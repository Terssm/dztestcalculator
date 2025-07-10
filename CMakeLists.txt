cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(CalcLib
    ICalculator.h
    SimpleCalculator.h SimpleCalculator.cpp
    IHistory.h
    InMemoryHistory.h InMemoryHistory.cpp
)


add_executable(CalculatorApp main.cpp)
target_link_libraries(CalculatorApp PRIVATE CalcLib)


enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(CalculatorTest
    tests/CalculatorTest.cpp
)

target_link_libraries(CalculatorTest
    PRIVATE CalcLib
    gtest
    gmock
    gtest_main
    gmock_main
)

add_test(NAME RunUnitTests COMMAND CalculatorTest)
