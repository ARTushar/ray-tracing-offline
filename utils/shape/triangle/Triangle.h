//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H


#include "../Shape.h"

class Triangle: public Shape {
private:
    Point p1, p2, p3;
    double rayIntersectsTriangle(const Ray &ray);
public:
    Triangle(const Point p1, const Point p2, const Point p3);
    void draw() override;
    void printShape() override;

    double intersect(const Ray &r, double *color, int level, const vector<Light *> lights,
                     const vector<Shape *> objects) override;

    Point get_normal_at(const Point &ins_point) override;
};


#endif //RAYTRACING_TRIANGLE_H
