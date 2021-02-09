cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(ft_containers
        list.hpp
        list_main.cpp)
