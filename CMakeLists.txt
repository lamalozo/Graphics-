cmake_minimum_required(VERSION 3.21)
project(untitled17)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled17 main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(untitled17 OpenGL::GL  GLUT::GLUT  GLEW::GLEW  -lfreeGLUT)
