//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H


#include "../point/Point.h"

class Light {
public:
  Point pos;
  double color[3];

  Light(const Point &pos, const double r, const double g, const double b);
  void printLight();
};


#endif //RAYTRACING_LIGHT_H
