cmake_minimum_required (VERSION 3.2.2)

project (bigword)

set (CMAKE_CXX_STANDARD 14)

# Just add -Wall -Wextra -Werror if using GCC or Clang.
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable (bigword
    src/analyzer.hpp src/analyzer.cpp
    src/clock.hpp src/clock.cpp
    src/digest.hpp src/digest.cpp
    src/option.hpp src/option.cpp
    src/rules.hpp src/rules.cpp
    src/store.hpp src/store.cpp
    src/word.hpp src/word.cpp
    src/main.cpp)

find_package (Threads REQUIRED)
find_package (OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories (${OPENSSL_INCLUDE_DIRS} ${THREADS_INCLUDE_DIRS})
    target_link_libraries (bigword ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif ()

# Copy needed data files.
add_custom_command (TARGET bigword PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lfs/words.txt ${CMAKE_BINARY_DIR}/words.txt)
