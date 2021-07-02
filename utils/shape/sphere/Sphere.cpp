//
// Created by tushar on 7/2/21.
//

#include "Sphere.h"
#include <GL/glut.h>
#include "../../drawShape/DrawShape.h"

using namespace std;

void Sphere::draw() {
  glPushMatrix(); {
    glTranslatef(ref_point.x, ref_point.y, ref_point.z);
    DrawShape::setColor(color[0], color[1], color[2]);
    DrawShape::drawSphere(length, 100, 100, 3);
  }
  glPopMatrix();
}

Sphere::Sphere(Point center, double radius) {
  shapeName = "Sphere";
  ref_point = center;
  length = radius;
}

void Sphere::printShape() {
  printf("Shape: %s\n", shapeName.c_str());
  printf("Center: %f %f %f\n", ref_point.x, ref_point.y, ref_point.z);
  printf("Radius: %f\n", length);
  Shape::printShape();
}
