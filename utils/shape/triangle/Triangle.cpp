//
// Created by tushar on 7/2/21.
//

#include "Triangle.h"
#include "../../drawShape/DrawShape.h";

void Triangle::draw() {
  DrawShape::setColor(color[0], color[1], color[2]);
  DrawShape::drawTriangle(p1, p2, p3);
}

void Triangle::printShape() {
  printf("Shape: %s\n", shapeName.c_str());
  printf("p1: %f %f %f\n", p1.x, p1.y, p1.z);
  printf("p2: %f %f %f\n", p2.x, p2.y, p2.z);
  printf("p3: %f %f %f\n", p3.x, p3.y, p3.z);
  Shape::printShape();
}

Triangle::Triangle(const Point p1, const Point p2, const Point p3): p1{p1}, p2{p2}, p3{p3} {
  shapeName = "Triangle";
}

double Triangle::intersect(const Ray &r, double *color, int level, const vector<Light *> lights,
                           const vector<Shape *> objects) {
  double t = rayIntersectsTriangle(r);
  if(t < 0) {
    return -1.0;
  } else {
    if(level == 0) return t;

    Point ins_point = r.start + r.dir * t;

    for(auto i = 0; i < 3; i++) {
      color[i] = this->color[i];
    }
    //
    if(level > 0) {
      illuminate(r, color, level, lights, objects, ins_point);
    }
    return t;
  }

}

double Triangle::rayIntersectsTriangle(const Ray &ray) {
  const float EPSILON = 0.0000001;
  Point edge1, edge2, h, s, q;
  float a,f,u,v;
  edge1 = p2 - p1;
  edge2 = p3 - p1;
  h = ray.dir.cross(edge2);
  a = edge1.dot(h);
  if (a > -EPSILON && a < EPSILON)
    return false;    // This ray is parallel to this triangle.
  f = 1.0/a;
  s = ray.start - p1;
  u = f * s.dot(h);
  if (u < 0.0 || u > 1.0)
    return -1.0;
  q = s.cross(edge1);
  v = f * ray.dir.dot(q);
  if (v < 0.0 || u + v > 1.0)
    return -1.0;
  // At this stage we can compute t to find out where the intersection point is on the line.
  float t = f * edge2.dot(q);
  if (t > EPSILON) // ray intersection
  {
    return t;
  }
  else // This means that there is a line intersection but not a ray intersection.
    return -1.0;
}

Point Triangle::get_normal_at(const Point &ins_point) {
  Point edge1, edge2;
  edge1 = p2 - p1;
  edge2 = p3 - p1;
  auto normal = edge1.cross(edge2);
  return normal.normalize();
}
