cmake_minimum_required(VERSION 2.8) 

project(HammingEncoder_lib)				

set(SOURCE_LIB HammingEncoder.cpp)	
set(HEADER_LIB HammingEncoder.h)

set(ENCODER_LIB_DIR HammingEncoder_lib)

add_library(HammingEncoder_lib STATIC ${SOURCE_LIB} ${HEADER_LIB})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")