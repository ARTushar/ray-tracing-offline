//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_FLOOR_H
#define RAYTRACING_FLOOR_H


#include "1605070_Shape.h"

class Floor: public Shape {
private:
    int total_tiles;
    void set_alt_color(const double r, const double g, const double b);
public:
    double alt_color[3];
    Floor(const double f_width, const double t_width, double r, double g, double b);
    void draw() override;

    double intersect(const Ray &r, double *color, int level, const vector<Light *> lights,
                     const vector<Shape *> objects) override;
    static void test();

    Point get_normal_at(const Point &ins_point) override;
};


#endif //RAYTRACING_FLOOR_H
