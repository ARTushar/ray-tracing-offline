//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H


#include "../Shape.h"

class Triangle: public Shape {
private:
    Point p1, p2, p3;
public:
    Triangle(const Point p1, const Point p2, const Point p3);

    void draw() override;

    void printShape() override;

};


#endif //RAYTRACING_TRIANGLE_H
