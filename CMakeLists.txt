cmake_minimum_required(VERSION 3.19)
project(Raytracing)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL)
file(GLOB SOURCES
        *.h
        *.cpp
        *.hpp
        )
add_executable(Raytracing ${SOURCES})
target_link_libraries(Raytracing ${OpenGlLinkers})
