cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB common_SRC
    "*.h"
    "*.cpp"
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    tests/
)

## Tests
project(SimpleMatrixTests VERSION 0.1.0)

file(GLOB test_SRC
    "tests/matrix/*.cpp"
    "tests/vector/*.cpp"
)

add_executable(SimpleMatrixTests 
    tests/testmain.cpp 
    ${common_SRC} 
    ${test_SRC}
)

## Time tests
project(SimpleMatrixTimeTests VERSION 0.1.0)

add_executable(SimpleMatrixTimeTests 
    tests/timetests.cpp 
    ${common_SRC}
)
