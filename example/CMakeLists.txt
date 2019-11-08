# Copyright(c) 2019 cppmath authors
# Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.1)
project(cppmath_examples CXX)

if(NOT TARGET cppmath)
    # Stand-alone build
    find_package(cppmath REQUIRED)
endif()

#---------------------------------------------------------------------------------------
# Example of using pre-compiled library
#---------------------------------------------------------------------------------------
add_executable(example example.cpp)
cppmath_enable_warnings(example)
target_link_libraries(example PRIVATE cppmath::cppmath)

#---------------------------------------------------------------------------------------
# Example of using header-only library
#---------------------------------------------------------------------------------------
if(CPPMATH_BUILD_EXAMPLE_HO)
    add_executable(example_header_only example.cpp)
    cppmath_enable_warnings(example_header_only)
    target_link_libraries(example_header_only PRIVATE cppmath::cppmath_header_only)
endif()
