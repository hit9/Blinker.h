cmake_minimum_required(VERSION 3.10)

project(blinker)

set(CMAKE_CXX_STANDARD 17)

add_library(blinker INTERFACE)
set_target_properties(blinker PROPERTIES PUBLIC_HEADER "blinker.h")

install(
  TARGETS blinker
  LIBRARY DESTINATION ${CMAK_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
