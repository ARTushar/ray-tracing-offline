//
// Created by tushar on 7/2/21.
//

#include "1605070_Shape.h"


Shape::Shape() {

}

void Shape::setColor(const double r, const double g, const double b) {
 color[0] = r;
 color[1] = g;
 color[2] = b;
}

void Shape::setCoefficients(const double am, const double di, const double sp, const double rco) {
  coefficients[0] = am;
  coefficients[1] = di;
  coefficients[2] = sp;
  coefficients[3] = rco;
}

void Shape::printShape() {
  printf("Color: %f %f %f\n", color[0], color[1], color[2]);
  printf("Coefficients: %f %f %f %f\n", coefficients[0], coefficients[1], coefficients[2], coefficients[3]);
  printf("Shininess: %d\n", shine);
}

double
Shape::intersect(const Ray &r, double *color, int level, const vector<Light *> lights, const vector<Shape *> objects) {
  return -1.0;
}

void Shape::draw() {

}

void
Shape::illuminate(const Ray &r, double *color, int level, const vector<Light *> lights, const vector<Shape *> objects,
                  const Point &ins_point) {
  auto *original_color = new double[3];
  for(auto i = 0; i < 3; i++) {
    original_color[i] = color[i];
    color[i] *= coefficients[0];
  }

  Point normal = get_normal_at(ins_point);

//  if (normal.dot(r.dir) > 0) {
//    normal = normal * -1.0;
//  }

  for(auto light: lights) {
    Point l_dir = light->pos - ins_point;
    auto distance = sqrt(l_dir.dot(l_dir));
    l_dir = l_dir.normalize();
    Ray l_ray(ins_point + l_dir, l_dir);

    bool in_shadow = false;
    auto dummy_color = new double[3];

//     checking if in shadow
    for(auto obj: objects) {
//      printf("shape: %s\n", obj->shapeName.c_str());
      auto t = obj->intersect(l_ray, dummy_color, 0, lights, objects);
      if(t > 0 && t < distance) {
        in_shadow = true;
        break;
      }
    }

    if(!in_shadow) {
      auto lamb_val = max(l_ray.dir.dot(normal), 0.0);
      // incident - 2 * (incident.normal)normal // here incident ray in opposite direction
      auto refl_ray_dir  =  normal * (2 * l_ray.dir.dot(normal)) - l_ray.dir;
      refl_ray_dir = refl_ray_dir.normalize();
      auto phong_val = max(r.dir.dot(refl_ray_dir), 0.0);

      for(int i = 0; i < 3; i++) {
        color[i] += light->color[i] * coefficients[1] * lamb_val * original_color[i];
        color[i] += light->color[i] * coefficients[2] * pow(phong_val, this->shine) * original_color[i];
      }
    }
  }

  if(level > 1) {
    Point ref_ray_dir = r.dir - normal * (2 * normal.dot(r.dir));
    ref_ray_dir = ref_ray_dir.normalize();
    Point ref_ray_start = ins_point + ref_ray_dir;
    Ray ref_ray(ref_ray_start, ref_ray_dir);

    auto *dummy_color = new double[3];
    auto *ref_color = new double[3];
    double min_pos_t = 1e9;
    Shape *closest_shape;
    for(auto obj: objects) {
      auto t = obj->intersect(ref_ray, dummy_color, 0, lights, objects);
      if(t > 0 && t < min_pos_t) {
        min_pos_t = t;
        closest_shape = obj;
      }
    }
    if(min_pos_t != 1e9) {
      closest_shape->intersect(ref_ray, ref_color, level-1, lights, objects);
      for(auto i = 0; i < 3; i++) {
        color[i] += ref_color[i] * coefficients[3];
      }
    }
  }
  clipColor(color);
}

Point Shape::get_normal_at(const Point &) {
  return {-1, -1, -1};
}

void Shape::clipColor(double *color) {
  for(auto i = 0; i < 3; i++) {
    if(color[i] > 1.0) color[i] = 1.0;
    if(color[i] < 0.0) color[i] = 0.0;
  }
}
