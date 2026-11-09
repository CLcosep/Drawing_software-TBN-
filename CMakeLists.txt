cmake_minimum_required(VERSION 3.10.0)
project(ArtProj)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ArtProj src/main.cpp src/glad.c)

target_include_directories(ArtProj PRIVATE include)
target_link_libraries(ArtProj
    glfw
    OpenGL::GL    
)