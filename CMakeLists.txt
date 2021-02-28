cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(list_test
        list.hpp
        tests/list_main.cpp)

add_executable(deque_test
        deque.hpp
        tests/deque_main.cpp)

add_executable(queue_test
        queue.hpp
        tests/queue_main.cpp)


add_executable(stack_test
        stack.hpp
        tests/stack_main.cpp)

add_executable(map_test
        rb_tree.hpp
        map.hpp
        tests/map_main.cpp)

add_executable(multimap_test
        rb_tree.hpp
        multimap.hpp
        tests/multimap_main.cpp)

add_executable(set_test
        rb_tree.hpp
        set.hpp
        tests/set_main.cpp)

add_executable(multiset_test
        rb_tree.hpp
        multiset.hpp
        tests/multiset_main.cpp)

add_executable(vector_test
        vector.hpp
        tests/vector_main.cpp)