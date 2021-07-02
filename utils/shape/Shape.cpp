//
// Created by tushar on 7/2/21.
//

#include "Shape.h"

Shape::Shape() {

}

void Shape::setColor(const double r, const double g, const double b) {
 color[0] = r;
 color[1] = g;
 color[2] = b;
}

void Shape::setCoefficients(const double am, const double di, const double sp, const double rco) {
  coefficients[0] = am;
  coefficients[1] = di;
  coefficients[2] = sp;
  coefficients[3] = rco;
}

void Shape::printShape() {
  printf("Color: %f %f %f\n", color[0], color[1], color[2]);
  printf("Coefficients: %f %f %f %f\n", coefficients[0], coefficients[1], coefficients[2], coefficients[3]);
  printf("Shininess: %d\n", shine);
}
