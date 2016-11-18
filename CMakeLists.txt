project (bigword)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat")

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable (bigword src/bigword.cpp)
