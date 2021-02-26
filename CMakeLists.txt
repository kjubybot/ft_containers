cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(list_test
        list.hpp
        list_main.cpp)

add_executable(deque_test
        deque.hpp
        deque_main.cpp)

add_executable(queue_test
        queue.hpp
        queue_main.cpp)


add_executable(stack_test
        stack.hpp
        stack_main.cpp)

add_executable(map_test
        rb_tree.hpp
        map.hpp
        map_main.cpp)