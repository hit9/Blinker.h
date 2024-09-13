cmake_minimum_required(VERSION 3.10)

project(BlinkerTests)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

enable_testing()

include_directories("../Source" ".")

find_package(Catch2 CONFIG REQUIRED)

# Targets
file(GLOB TEST_SOURCES *.cpp)
add_executable(BlinkerTests ${TEST_SOURCES})

target_link_libraries(BlinkerTests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(BlinkerTests)
