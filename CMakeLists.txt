cmake_minimum_required(VERSION 3.21)

project(pybezier)

find_package(OpenMP REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/pybind11)

pybind11_add_module( ${CMAKE_PROJECT_NAME} 
    src/bindings.cpp
    src/utils.cpp
    src/vec2.cpp
    src/bezier.cpp    
)

if(OpenMP_CXX_FOUND)
    message("-- found OpenMP")
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()

include_directories(include)