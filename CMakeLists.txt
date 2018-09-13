cmake_minimum_required(VERSION 3.10)
project(eim)

set(CMAKE_BUILD_TYPE Debug)

# GRPC and Protocol Buffers libraries location
set(CMAKE_PREFIX_PATH /usr/local)
# Cmake find modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3") # -O0 / -O3
set(CMAKE_CXX_STANDARD 11)

# Set dirs
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE EIM_SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE EIM_HEADERS ${SRC_DIR}/*.h)

message("Compiling ${EIM_SOURCES}")

add_executable(eim ${EIM_SOURCES} ${EIM_HEADERS})
# Define requirements
target_include_directories(eim PUBLIC)
target_link_libraries(eim)