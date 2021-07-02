//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_FLOOR_H
#define RAYTRACING_FLOOR_H


#include "../Shape.h"

class Floor: public Shape {
private:
    int total_tiles;
public:
    double alt_color[3];
    Floor(const double f_width, const double t_width, double r, double g, double b);
    void set_alt_color(const double r, const double g, const double b);
    void draw() override;
};


#endif //RAYTRACING_FLOOR_H
