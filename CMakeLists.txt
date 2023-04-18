cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

project(opencv)
message(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CURRENT_BINARY_DIR bin/)
set(CMAKE_SOURCE_DIR src/)
set(PROJECT_SOURCE_DIR "src/")
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
add_compile_options(-g -O0)

# file(GLOB  APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp)
AUX_SOURCE_DIRECTORY(./src APP_SOURCES)
message(ABC=${APP_SOURCES})
message(bin=${CMAKE_BINARY_DIR})
# message(ABC=${CMAKE_CURRENT_SOURCE_DIR})

foreach( testsourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    string( REPLACE "./src/" "" testname ${testname} )
    add_executable( ${testname} ${testsourcefile} )
    # Make sure YourLib is linked to each app
    # target_link_libraries( ${testname} YourLib )
endforeach( testsourcefile ${APP_SOURCES} )