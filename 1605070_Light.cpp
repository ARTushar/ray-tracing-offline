//
// Created by tushar on 7/2/21.
//

#include <cstdio>
#include "1605070_Light.h"
#include "1605070_DrawShape.h"

using namespace std;

Light::Light(const Point &pos, const double r, const double g, const double b) {
  this->pos = pos;
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

void Light::printLight() {
  printf("position: %f %f %f\n", pos.x, pos.y, pos.z);
  printf("color: %f %f %f\n", color[0], color[1], color[2]);
}

void Light::draw() {
  glPushMatrix(); {
    glTranslatef(pos.x, pos.y, pos.z);
    DrawShape::setColor(color[0], color[1], color[2]);
    DrawShape::drawSphere(2, 50, 30, 3);
  }
  glPopMatrix();
}
