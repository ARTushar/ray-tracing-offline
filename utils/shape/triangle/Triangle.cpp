//
// Created by tushar on 7/2/21.
//

#include "Triangle.h"
#include "../../drawShape/DrawShape.h";

void Triangle::draw() {
  DrawShape::setColor(color[0], color[1], color[2]);
  DrawShape::drawTriangle(p1, p2, p3);
}

void Triangle::printShape() {
  printf("Shape: %s\n", shapeName.c_str());
  printf("p1: %f %f %f\n", p1.x, p1.y, p1.z);
  printf("p2: %f %f %f\n", p2.x, p2.y, p2.z);
  printf("p3: %f %f %f\n", p3.x, p3.y, p3.z);
  Shape::printShape();
}

Triangle::Triangle(const Point p1, const Point p2, const Point p3): p1{p1}, p2{p2}, p3{p3} {
  shapeName = "Triangle";
}
