cmake_minimum_required(VERSION 3.10)
project(LearnGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearnGL main.cpp glad.c image_impl.cpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(LearnGL PRIVATE glfw)