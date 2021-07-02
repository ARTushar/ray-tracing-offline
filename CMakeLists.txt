cmake_minimum_required(VERSION 3.19)
project(Raytracing)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(Raytracing main.cpp utils/cameraHandler/CameraHandler.h utils/cameraHandler/CameraHandler.cpp utils/drawShape/DrawShape.cpp utils/drawShape/DrawShape.h utils/constants/Constants.h utils/point/Point.h utils/image/bitmap_image.hpp opengl/Opengl.cpp opengl/Opengl.h utils/shape/Shape.cpp utils/shape/Shape.h utils/shape/triangle/Triangle.cpp utils/shape/triangle/Triangle.h utils/shape/sphere/Sphere.cpp utils/shape/sphere/Sphere.h utils/shape/general/General.cpp utils/shape/general/General.h utils/light/Light.cpp utils/light/Light.h raytracing/Raytracing.cpp raytracing/Raytracing.h utils/command/Command.h utils/shape/floor/Floor.cpp utils/shape/floor/Floor.h)
target_link_libraries(Raytracing ${OpenGlLinkers})
