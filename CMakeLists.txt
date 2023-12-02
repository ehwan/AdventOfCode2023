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
