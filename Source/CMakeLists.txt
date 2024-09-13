cmake_minimum_required(VERSION 3.10)

project(Blinker)

set(CMAKE_CXX_STANDARD 17)

add_library(Blinker INTERFACE)
set_target_properties(Blinker PROPERTIES PUBLIC_HEADER "Blinker.h")

install(
  TARGETS Blinker
  LIBRARY DESTINATION ${CMAK_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
