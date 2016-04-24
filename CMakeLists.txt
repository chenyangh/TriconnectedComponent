project(triconnected_component)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(triconnected_component Tricomp.cpp main.cpp)

install(TARGETS triconnected_component RUNTIME DESTINATION bin)

add_library(Tricomp SHARED Tricomp.cpp)
