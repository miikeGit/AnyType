cmake_minimum_required(VERSION 3.31)
project(Task2)

set(CMAKE_CXX_STANDARD 20)

# --- Google Test Integration ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Main Executable ---
add_executable(Task2 main.cpp AnyType.h)

# --- Testing ---
enable_testing()
include(GoogleTest)

# Add the test executable
add_executable(runTests tests.cpp AnyType.h)

# Link the test executable with GTest
target_link_libraries(runTests PRIVATE GTest::gtest_main)

# Discover and add tests
gtest_discover_tests(runTests)
