cmake_minimum_required(VERSION 3.10)

project(blinker_tests)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

enable_testing()

include_directories(".." ".")

find_package(Catch2 CONFIG REQUIRED)

# Targets
file(GLOB TEST_SOURCES *_test.cc)
add_executable(blinker_tests ${TEST_SOURCES})

target_link_libraries(blinker_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(blinker_tests)
