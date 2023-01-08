cmake_minimum_required(VERSION 3.21)
project(NetSim)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(NetSim
        package.cpp
        package.hpp
        storage_types.cpp
        storage_types.hpp
        types.hpp)
