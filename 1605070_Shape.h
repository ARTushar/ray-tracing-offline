//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_SHAPE_H
#define RAYTRACING_SHAPE_H


#include <string>
#include <vector>
#include "1605070_Point.h"
#include "1605070_Ray.h"
#include "1605070_Light.h"

using namespace std;

class Shape {
public:
    Point ref_point;
    std::string shapeName;
    double height, width, length;
    double color[3];
    double coefficients[4];
    int shine;

    Shape();
    virtual void draw();
    virtual void printShape();
    virtual double
    intersect(const Ray &r, double *color, int level, const vector<Light *> lights, const vector<Shape *> objects);
    void setColor(const double r, const double g, const double b);
    void setCoefficients(const double am, const double di, const double sp, const double rco);
    void illuminate(const Ray &r, double *color, int level, const vector<Light *> lights, const vector<Shape *> objects,
                    const Point &ins_point);
    virtual Point get_normal_at(const Point &ins_point);
    void clipColor(double *color);
};


#endif //RAYTRACING_SHAPE_H
