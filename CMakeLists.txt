cmake_minimum_required (VERSION 3.4)

project (bigword)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat")

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable (bigword src/bigword.cpp)

# Copy needed data files.
add_custom_command (TARGET bigword PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lfs/words.txt ${CMAKE_BINARY_DIR}/words.txt)
