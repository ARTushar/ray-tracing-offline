//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H


#include "../Shape.h"

class Sphere: public Shape {
public:
    Sphere(Point center, double radius);
    void draw() override;

    void printShape() override;
};


#endif //RAYTRACING_SPHERE_H
