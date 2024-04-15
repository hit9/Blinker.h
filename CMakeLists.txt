cmake_minimum_required(VERSION 3.10)

project(blinker)

option(BLINKER_TEST "Enables testing" OFF)

add_library(blinker INTERFACE)
set_target_properties(blinker PROPERTIES PUBLIC_HEADER "blinker.h")

if(BLINKER_TEST)
  # add_subdirectory(tests EXCLUDE_FROM_ALL)
  add_subdirectory(example EXCLUDE_FROM_ALL)
endif()

install(
  TARGETS blinker
  LIBRARY DESTINATION ${CMAK_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
