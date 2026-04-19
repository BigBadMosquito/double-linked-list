cmake_minimum_required(VERSION 3.15)

project(double_linked_list CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/double_linked_list.cpp
    src/double_linked_list.h
    src/rand_index_resolver.cpp
    src/rand_index_resolver.h
    src/linked_list_wish_rand.cpp
    src/linked_list_wish_rand.h
    src/list_node.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)