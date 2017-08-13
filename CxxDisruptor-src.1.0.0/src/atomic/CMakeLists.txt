cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

# activate C++11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

aux_source_directory(. SRC_LIST)
