//
// Created by tushar on 7/2/21.
//

#include "General.h"

void General::draw() {

}

void General::printShape() {
  printf("Shape: %s\n", shapeName.c_str());
  printf("%f %f %f %f %f %f %f %f %f %f\n", a, b, c, d ,e, f, g, h, i ,j);
  printf("reference point: %f %f %f\n", ref_point.x, ref_point.y, ref_point.z);
  printf("length: %f\twidth: %f\theight: %f\n", length, width, height);
  Shape::printShape();
}

General::General(const double a, const double b, const double c, const double d, const double e, const double f,
                 const double g, const double h, const double i, const double j, const Point ref, const double length,
                 const double width, const double height):
    a{a}, b{b}, c{c}, d{d}, e{e}, f{f}, g{g}, h{h}, i{i}, j{j}{
  shapeName = "General";
  ref_point = ref;
  this->length = length;
  this->height = height;
  this->width = width;
}

double General::intersect(const Ray &r, double *color, int level, const vector<Light *> lights,
                          const vector<Shape *> objects) {
  double t = intersect_ray(r);
  if(t < 0) {
    return -1.0;
  } else {


    if(level == 0) return t;
    for(auto i = 0; i < 3; i++) {
      color[i] = this->color[i];
    }
    //
    Point ins_point = r.start + r.dir * t;
    if(level > 0) {
      illuminate(r, color, level, lights, objects, ins_point);
    }
    return t;
  }

}

double General::intersect_ray(const Ray &r) {
  const float EPSILON = 0.0000001;
  auto t_start = r.start - ref_point;
  auto dir = r.dir;
  double aq = a * dir.x * dir.x
              + b * dir.y * dir.y
              + c * dir.z * dir.z
              + d * dir.x * dir.y
              + e * dir.y * dir.z
              + f * dir.z * dir.x;
  double bq = 2 * a * t_start.x * dir.x
              + 2 * b * t_start.y * dir.y
              + 2 * c * t_start.z * dir.z
              + d * (t_start.x * dir.y + t_start.y * dir.x)
              + e * (t_start.y * dir.z + t_start.z * dir.y)
              + f * (t_start.x * dir.z + t_start.z * dir.x)
              + g * dir.x + h * dir.y + i * dir.z;
  double cq = a * t_start.x * t_start.x
              + b * t_start.y * t_start.y
              + c * t_start.z * t_start.z
                + d * t_start.x * t_start.y
                + e * t_start.y * t_start.z
                + f * t_start.z * t_start.x
                + g * t_start.x + h * t_start.y + i * t_start.z + j;

  if(abs(aq) < EPSILON) {
    return - (cq / bq);
  } else {
    auto det = (bq * bq) - (4 * aq * cq);
    if(det < 0.0) return -1.0;
    auto t_plus = (-bq + sqrt(det)) / (2.0 * aq);
    auto t_min = (-bq - sqrt(det)) / (2.0 * aq);
    if(t_min > 0) {
      Point ins_point = r.start + r.dir * t_min;
      auto hidden = check_condition(ins_point);
      if(!hidden) return t_min;
      ins_point = r.start + r.dir * t_plus;
      hidden = check_condition(ins_point) ;
      if(!hidden) return t_plus;
    }
    else {
      auto ins_point = r.start + r.dir * t_plus;
      bool hidden = check_condition(ins_point) ;
      if(!hidden) return t_plus;
    }
  }
  return -1.0;
}

Point General::get_normal_at(const Point &ins_point) {
  auto xn = 2 * a * ins_point.x + d * ins_point.y + e * ins_point.z + g;
  auto yn = 2 * b * ins_point.y + d * ins_point.x + f * ins_point.z + h;
  auto zn = 2 * c * ins_point.z + e * ins_point.y + f * ins_point.x + i;
  Point normal{xn, yn, zn};
  return normal.normalize();
}

bool General::check_condition(const Point &ins_point) {
  if( (length == 0 || (ins_point.x >= ref_point.x - length / 2
                       && ins_point.x <= ref_point.x + length / 2))
      && (width == 0 || (ins_point.y >= ref_point.y - width / 2
                         && ins_point.y <= ref_point.y + width / 2))
      && (height == 0 || (ins_point.z >= ref_point.z
                          && ins_point.z <= ref_point.z + height ))) {
    return false;
  }
  return true;
}
