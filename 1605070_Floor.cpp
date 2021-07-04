//
// Created by tushar on 7/2/21.
//

#include "1605070_Floor.h"
#include "1605070_DrawShape.h"
#include <GL/glut.h>

void Floor::draw() {
  bool alt = true;
  for(int i = 0; i < total_tiles; i++) {
    for(int j = 0; j < total_tiles; j++) {
      if(alt) DrawShape::setColor(color[0], color[1], color[2]);
      else DrawShape::setColor(alt_color[0], alt_color[1], alt_color[2]);
      DrawShape::drawTile({ref_point.x + j * length, ref_point.y + i * length, ref_point.z}, length);
      alt = !alt;
    }
    alt = !alt;
  }
}

void Floor::set_alt_color(double r, const double g, const double b) {
  alt_color[0] = r;
  alt_color[1] = g;
  alt_color[2] = b;
}

Floor::Floor(const double f_width, const double t_width, double r, double g, double b) {
  shapeName = "Floor";
  ref_point = {-f_width/2, -f_width/2, 0};
  length = t_width;
  set_alt_color(r, g, b);
  total_tiles = floor(f_width / t_width);
}

double
Floor::intersect(const Ray &r, double *color, int level, const vector<Light *> lights, const vector<Shape *> objects) {
  Point center = {0, 0, 0};
  Point normal(0, 0, 1);
  auto D = center.dot(normal);

  auto den = normal.dot(r.dir);
  if(den == 0) return -1.0;
  auto t = -(D + normal.dot(r.start)) / den;

  auto point = r.start + r.dir * t;

  if(point.x >= ref_point.x && point.x <= ref_point.x + total_tiles * length &&
     point.y >= ref_point.y && point.y <= ref_point.y + total_tiles * length
      ) {
    int tile_no_w = floor((point.x - ref_point.x) / length);
    int tile_no_h = floor((point.y - ref_point.y) / length);
    if((tile_no_w + tile_no_h) % 2) {
      color[0] = this->alt_color[0];
      color[1] = this->alt_color[1];
      color[2] = this->alt_color[2];
    } else {
      color[0] = this->color[0];
      color[1] = this->color[1];
      color[2] = this->color[2];
    }

    if(level > 0) {
      illuminate(r, color, level, lights, objects, point);
    }

    return t;
  } else {
    return -1.0;
  }
}

void Floor::test() {
  Floor floor1(1000, 20, 0, 0, 0);
  floor1.setColor(1, 1, 1);

  Point dir = {1, -1, -1};
  dir = dir.normalize();
  Ray ray({-12, 10, 1}, dir);

//  auto color = new double [3];
//  auto ins = floor1.intersect(ray, color, 1, 0, vector<Shape *>());
//  printf("Ins t: %f\n", ins);
//  auto ins_point = ray.start + ray.dir * ins;
//  if(ins > 0) {
//    printf("Intersecting point: %f %f %f\n", ins_point.x, ins_point.y, ins_point.z);
//    printf("Colors: %f %f %f\n", color[0], color[1], color[2]);
//  } else {
//    printf("Not intersected\n");
//  }
}

Point Floor::get_normal_at(const Point &ins_point) {
  return {0, 0, 1};
}

