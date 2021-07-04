//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H


#include "1605070_Shape.h"

class Sphere: public Shape {
public:
    Sphere(Point center, double radius);
    void draw() override;

    double intersect(const Ray &r, double *color, int level, const vector<Light *> lights,
                     const vector<Shape *> objects) override;
    void printShape() override;

    Point get_normal_at(const Point &ins_point) override;

    static void test();
};


#endif //RAYTRACING_SPHERE_H
