//
// Created by tushar on 7/2/21.
//

#include "General.h"

void General::draw() {

}

void General::printShape() {
  printf("Shape: %s\n", shapeName.c_str());
  printf("%f %f %f %f %f %f %f %f %f %f\n", a, b, c, d ,e, f, g, h, i ,j);
  printf("reference point: %f %f %f\n", ref_point.x, ref_point.y, ref_point.z);
  printf("length: %f\twidth: %f\theight: %f\n", length, width, height);
  Shape::printShape();
}

General::General(const double a, const double b, const double c, const double d, const double e, const double f,
                 const double g, const double h, const double i, const double j, const Point ref, const double length,
                 const double width, const double height):
    a{a}, b{b}, c{c}, d{d}, e{e}, f{f}, g{g}, h{h}, i{i}, j{j}{
  shapeName = "General";
  ref_point = ref;
  this->length = length;
  this->height = height;
  this->width = width;
}
