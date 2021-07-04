//
// Created by tushar on 7/3/21.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "1605070_Point.h"

class Ray {
public:
    Point start;
    Point dir; // normalize

    Ray(const Point start, const Point dir);
};


#endif //RAYTRACING_RAY_H
