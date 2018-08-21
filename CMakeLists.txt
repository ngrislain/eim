cmake_minimum_required(VERSION 3.10)
project(eim)

set(CMAKE_BUILD_TYPE Debug)

# GRPC and Protocol Buffers libraries location
set(CMAKE_PREFIX_PATH /usr/local)
# Cmake find modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 11)

# Find main packages
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Boost COMPONENTS system math_tr1 python37 numpy37 REQUIRED)

# Set dirs
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXTERNAL_DIR ~/Git/external)
set(RANGE_INCLUDE_DIR ${EXTERNAL_DIR}/range-v3/include)
#set(MATPLOTLIB_INCLUDE_DIR ${EXTERNAL_DIR}/matplotlib-cpp)
#set(JSON_INCLUDE_DIR ${EXTERNAL_DIR}/json/include)
set(NUMPY_INCLUDE_DIR /usr/local/lib/python3.7/site-packages/numpy/core/include)

file(GLOB_RECURSE EIM_SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE EIM_HEADERS ${SRC_DIR}/*.h)

message("Compiling ${EIM_SOURCES}")

add_executable(eim ${EIM_SOURCES} ${EIM_HEADERS})
# Define requirements
target_include_directories(eim PUBLIC ${Boost_INCLUDE_DIRS} ${Python3_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR} ${RANGE_INCLUDE_DIR})
target_link_libraries(eim ${Boost_LIBRARIES} ${Python3_LIBRARIES})