cmake_minimum_required(VERSION 3.9)

project(bigword)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Just add our own flags if using GCC or Clang.
if(
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"
    OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"
)
    message("Compiler is GCC/Clang, using a lot of warnings.")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wunreachable-code -Wreturn-type -Werror"
    )
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
        add_compile_options(-fsanitize=undefined)
        add_link_options(-fsanitize=undefined)
        add_compile_options(-fsanitize=leak)
        add_link_options(-fsanitize=leak)
    endif()
endif()

if(
    "${CMAKE_BUILD_TYPE}" STREQUAL "Release"
    OR "${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel"
)
    message("Release build, setting IPO.")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set(BIGWORD_DEFAULT_SOURCE "source.txt")

set(BIGWORD_DEFAULT_LICENSE "license.txt")

configure_file(
    "${PROJECT_SOURCE_DIR}/sources/configuration.hpp.in"
    "${PROJECT_BINARY_DIR}/sources/configuration.hpp"
)

# Add the binary tree to the search path for include files so that we will find it.
include_directories("${PROJECT_BINARY_DIR}/sources/")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(
    bigword
    sources/linenumber.hpp
    sources/linestream.hpp
    sources/linestream.cpp
    sources/analyzer.hpp
    sources/analyzer.cpp
    sources/license.hpp
    sources/license.cpp
    sources/digest.hpp
    sources/digest.cpp
    sources/option.hpp
    sources/option.cpp
    sources/clock.hpp
    sources/clock.cpp
    sources/rules.hpp
    sources/rules.cpp
    sources/store.hpp
    sources/store.cpp
    sources/data.hpp
    sources/data.cpp
    sources/word.hpp
    sources/word.cpp
    sources/main.cpp
)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIRS} ${THREADS_INCLUDE_DIRS})
target_link_libraries(bigword ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Copy needed data files.
add_custom_command(
    TARGET bigword
    PRE_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/LICENSE.txt
        ${CMAKE_BINARY_DIR}/${BIGWORD_DEFAULT_LICENSE}
    COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/en/words/words.txt
        ${CMAKE_BINARY_DIR}/${BIGWORD_DEFAULT_SOURCE}
)
