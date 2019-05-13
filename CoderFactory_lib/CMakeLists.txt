cmake_minimum_required(VERSION 2.8) 

project(CoderFactory_lib)				

set(SOURCE_LIB CoderFactory.cpp)	
set(HEADER_LIB CoderFactory.h)

set(CALCULATOR_LIB_DIR CoderFactory_lib)

add_library(CoderFactory_lib STATIC ${SOURCE_LIB} ${HEADER_LIB})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")