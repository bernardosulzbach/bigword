cmake_minimum_required (VERSION 3.2.2)

project (bigword)

set (CMAKE_CXX_STANDARD 14)

# Just add -Wall -Wextra -Werror if using GCC or Clang.
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable (bigword
    src/option.hpp src/option.cpp
    src/clock.hpp src/clock.cpp
    src/word.hpp src/word.cpp
    src/main.cpp)

# Copy needed data files.
add_custom_command (TARGET bigword PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lfs/words.txt ${CMAKE_BINARY_DIR}/words.txt)
