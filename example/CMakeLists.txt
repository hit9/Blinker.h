cmake_minimum_required(VERSION 3.10)
project(bt_example CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("..")

# Targets
add_executable(blinker_example main.cc)
