cmake_minimum_required(VERSION 4.3)
project(ADALab2_DynamicArray)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ADALab2_DynamicArray_Tests
    Array.h
    tests/TestsWithInts.cpp
    tests/TestsWithStrings.cpp
    tests/TestsWithPODs.cpp
    tests/TestsWithMovables.cpp
    tests/TestsWithUnmovables.cpp
    tests/TestsThatOverloads.cpp
        tests/TestClasses.h
)

target_link_libraries(
    ADALab2_DynamicArray_Tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ADALab2_DynamicArray_Tests)
