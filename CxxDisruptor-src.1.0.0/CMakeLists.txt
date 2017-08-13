cmake_minimum_required(VERSION 2.8)

project(CxxDisruptor)

# activate C++11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# activate multi threading
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")

# Disregard strict standards compliance. -Ofast enables all -O3 optimizations.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

set(CMAKE_BUILD_TYPE "Debug")



aux_source_directory(./src SRC_LIST)
aux_source_directory(./src/disruptor SRC_LIST)
aux_source_directory(./src/atomic SRC_LIST)
aux_source_directory(./src/base SRC_LIST)

include_directories(./src/atomic ./src/disruptor ./src/base)


#add_subdirectory(./src)

#aux_source_directory(./src SRC_LIST)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
add_executable(${PROJECT_NAME}-exe ${SRC_LIST})

# activate C++11 features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# add my tests
add_subdirectory(./test)

