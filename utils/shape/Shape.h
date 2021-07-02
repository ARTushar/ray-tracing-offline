//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_SHAPE_H
#define RAYTRACING_SHAPE_H


#include <string>
#include "../point/Point.h"

class Shape {
public:
    Point ref_point;
    std::string shapeName;
    double height, width, length;
    double color[3];
    double coefficients[4];
    int shine;

    Shape();
    virtual void draw() = 0;
    virtual void printShape();
    void setColor(const double r, const double g, const double b);
    void setCoefficients(const double am, const double di, const double sp, const double rco);

};


#endif //RAYTRACING_SHAPE_H
