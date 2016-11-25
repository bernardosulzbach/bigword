cmake_minimum_required (VERSION 3.2.2)

project (bigword)

set (CMAKE_CXX_STANDARD 14)

# Just add -Wall -Wextra -Werror if using GCC or Clang.
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable (bigword
    src/linenumber.hpp
    src/linestream.hpp src/linestream.cpp
    src/analyzer.hpp src/analyzer.cpp
    src/digest.hpp src/digest.cpp
    src/option.hpp src/option.cpp
    src/clock.hpp src/clock.cpp
    src/rules.hpp src/rules.cpp
    src/store.hpp src/store.cpp
    src/data.hpp src/data.cpp
    src/word.hpp src/word.cpp
    src/main.cpp)

find_package (OpenSSL REQUIRED)
find_package (Threads REQUIRED)
include_directories (${OPENSSL_INCLUDE_DIRS} ${THREADS_INCLUDE_DIRS})
target_link_libraries (bigword ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Copy needed data files.
add_custom_command (TARGET bigword PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lfs/en/words.txt ${CMAKE_BINARY_DIR}/words.txt)
