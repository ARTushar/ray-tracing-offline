//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_GENERAL_H
#define RAYTRACING_GENERAL_H


#include "1605070_Shape.h"

class General: public Shape {
private:
    double a, b, c, d, e, f, g, h, i, j;
public:
    General(const double a, const double b, const double c, const double d,const double e, const double f, const double g, const double h, const double i, const double j, const Point ref, const double length, const double width, const double height);
    void draw() override;
    void printShape() override;

    double intersect(const Ray &r, double *color, int level, const vector<Light *> lights,
                     const vector<Shape *> objects) override;
    double intersect_ray(const Ray &r);

    Point get_normal_at(const Point &ins_point) override;
    bool check_condition(const Point &ins_point);
};


#endif //RAYTRACING_GENERAL_H
