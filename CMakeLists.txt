cmake_minimum_required( VERSION 3.20 )

set( CMAKE_CXX_COMPILER /usr/bin/clang++ )


project( Day1 CXX )
add_executable( Day1
  Day1.cpp
)
set_target_properties(
  Day1
  PROPERTIES
  CXX_STANDARD 17
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)

project( Day1-2 CXX )
add_executable( Day1-2
  Day1-2.cpp
)
set_target_properties(
  Day1-2
  PROPERTIES
  CXX_STANDARD 17
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)

project( Day2 CXX )
add_executable( Day2
  Day2.cpp
)
set_target_properties(
  Day2
  PROPERTIES
  CXX_STANDARD 17
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin
)