cmake_minimum_required(VERSION 3.10)
project(eim)

# GRPC and Protocol Buffers libraries location
set(CMAKE_PREFIX_PATH /usr/local)
# Cmake find modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
# Set C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

# Find main packages
find_package(PythonInterp)
find_package(PythonLibs)
find_package(Boost COMPONENTS system math_tr1 python27 REQUIRED)

# Set external includes
set(EXTERNAL_DIR ~/Git/external)
set(RANGE_DIR ${EXTERNAL_DIR}/range-v3/include)
set(RANGE_DIR ${EXTERNAL_DIR}/matplotlib-cpp)
set(JSON_DIR ${EXTERNAL_DIR}/json/include)
set(NUMPY_DIR /System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include)

file(GLOB EIM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB EIM_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

message("Compiling ${EIM_SOURCES}")

add_executable(eim ${EIM_SOURCES} ${EIM_HEADERS})
# Define requirements
#target_include_directories(eim PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIR})
#target_link_libraries(eim ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(eim PUBLIC ${Boost_INCLUDE_DIRS} ${RANGE_DIR} ${JSON_DIR} ${PYTHON_INCLUDE_DIR} ${NUMPY_DIR})
#target_include_directories(eim PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(eim ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})