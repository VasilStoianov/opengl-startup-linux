cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyProject main.cpp glad.c)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(MyProject PRIVATE glfw)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
