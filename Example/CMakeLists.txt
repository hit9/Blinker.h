cmake_minimum_required(VERSION 3.10)
project(BlinkerExample CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("../Source")

# Targets
add_executable(BlinkerExample main.cpp)
