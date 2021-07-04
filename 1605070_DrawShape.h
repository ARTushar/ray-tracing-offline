//
// Created by tushar on 3/14/21.
//
#include <string>
#include <cmath>
#include <GL/glut.h>
#include "1605070_Point.h"
#ifndef INC_1605070_DRAWSHAPE_H
#define INC_1605070_DRAWSHAPE_H


class DrawShape {
private:
    static double cr, cg, cb;
public:
    static void drawCylinder(double radius, int slices, int stacks, double height, double arcRadius);
    static void drawSphere(double radius, int slices, int stacks, int dir);
    static void drawAxes(double length);
    static void drawPlane(Point center, double width, double height);
    static void drawSquare(Point position, double length, Point color);
    static void drawSquareXY(Point position, double length, Point color);
    static void drawCircleXY(Point position, double radius, Point color);
    static void drawTriangle(const Point &p1, const  Point &p2, const Point &p3);
    static void drawTile(const Point &bottom_left, const double length);
    static void setColor(double r, double g, double b);
};


#endif //INC_1605070_DRAWSHAPE_H
