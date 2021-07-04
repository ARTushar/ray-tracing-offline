//
// Created by tushar on 7/2/21.
//

#include "1605070_Sphere.h"
#include <GL/glut.h>
#include <vector>
#include "1605070_DrawShape.h"

using namespace std;

void Sphere::draw() {
  glPushMatrix(); {
    glTranslatef(ref_point.x, ref_point.y, ref_point.z);
    DrawShape::setColor(color[0], color[1], color[2]);
    DrawShape::drawSphere(length, 100, 100, 3);
  }
  glPopMatrix();
}

Sphere::Sphere(Point center, double radius) {
  shapeName = "Sphere";
  ref_point = center;
  length = radius;
}

void Sphere::printShape() {
  printf("Shape: %s\n", shapeName.c_str());
  printf("Center: %f %f %f\n", ref_point.x, ref_point.y, ref_point.z);
  printf("Radius: %f\n", length);
  Shape::printShape();
}

double
Sphere::intersect(const Ray &r, double *color, int level, const vector<Light *> lights, const vector<Shape *> objects) {

  auto translated_start = r.start - ref_point;

  auto a = 1;
  auto b = 2 * r.dir.dot(translated_start);
  auto c = translated_start.dot(translated_start) - length * length;

  if(b*b - 4*a*c < 0) return -1.0;

  auto d = sqrt(b*b - 4*a*c);
  auto t_plus = (-b + d) / (2.0*a);
  auto t_min = (-b - d) / (2.0*a);
  double t_final;

  if(t_plus >= 0 && t_min >= 0) {
    t_final = min(t_plus, t_min);
  } else {
    t_final = max(t_plus, t_min);
  }

  if(level == 0) return t_final;

  Point ins_point = r.start + r.dir * t_final;

  for(auto i = 0; i < 3; i++) {
    color[i] = this->color[i];
  }
  //
  if(level > 0) {
    illuminate(r, color, level, lights, objects, ins_point);
  }

  return t_min;

}

void Sphere::test() {
  Sphere sphere({0, 0, 0}, 10);
  Point dir = {1, -1, 0};
  dir = dir.normalize();
  Ray ray({-12, 10, 0}, dir);

//  auto color = new double [3];
//  auto ins = sphere.intersect(ray, color, 1, );
//  printf("Ins t: %f\n", ins);
//  auto ins_point = ray.start + ray.dir * ins;
//  if(ins > 0) {
//    printf("Intersecting point: %f %f %f\n", ins_point.x, ins_point.y, ins_point.z);
//  } else {
//    printf("Not intersected\n");
//  }
}

Point Sphere::get_normal_at(const Point &ins_point) {
  return (ins_point-ref_point).normalize();
}

