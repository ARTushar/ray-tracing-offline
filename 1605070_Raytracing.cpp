//
// Created by tushar on 7/2/21.
//

#include "1605070_Raytracing.h"
#include "1605070_Sphere.h"
#include "1605070_General.h"
#include "1605070_Triangle.h"
#include "1605070_Floor.h"
#include "1605070_bitmap_image.hpp"
#include "1605070_Constants.h"
#include "1605070_Ray.h"


bool Raytracing::DEBUG = false;

void Raytracing::parse_command(const COMMAND &command) {
  switch (command) {
    case TRIANGLE:
      parse_triangle();
      break;
    case SPHERE:
      parse_sphere();
      break;
    case GENERAL:
      parse_general();
      break;
    default:
      break;
  }
}

void Raytracing::parse_triangle() {
  double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, cr, cg, cb, am, di, sp, rco;
  int shine;
  input_file >> p1x >> p1y >> p1z >> p2x >> p2y >> p2z >> p3x >> p3y >> p3z >> cr >> cg >> cb >> am >> di >> sp >> rco >> shine;
  Shape *temp = new Triangle({p1x, p1y, p1z}, {p2x, p2y, p2z}, {p3x, p3y, p3z});
  temp->setColor(cr, cg, cb);
  temp->setCoefficients(am, di, sp, rco);
  temp->shine = shine;

  objects.push_back(temp);
}

void Raytracing::parse_sphere() {
  double cx, cy, cz, r, cr, cg, cb, am, di, sp, rco;
  int shine;
  input_file >> cx >> cy >> cz >> r >> cr >> cg >> cb >> am >> di >> sp >> rco >> shine;
  Shape *temp = new Sphere({cx, cy, cz}, r);
  temp->setColor(cr, cg, cb);
  temp->setCoefficients(am, di, sp, rco);
  temp->shine = shine;

  objects.push_back(temp);
}

void Raytracing::parse_general() {
  double a, b, c, d, e, f, g, h, i, j, ref_x, ref_y, ref_z, len, wid, hei, cr, cg, cb, am, di, sp, rf;
  int shine;
  input_file >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> ref_x >> ref_y >> ref_z >> len >> wid >> hei >> cr >> cg >> cb >> am >> di >> sp >> rf >> shine;
  Shape *temp = new General(a, b, c, d, e, f, g, h, i, j, {ref_x, ref_y, ref_z}, len, wid, hei);
  temp->setColor(cr, cg, cb);
  temp->setCoefficients(am, di, sp, rf);
  temp->shine = shine;

  objects.push_back(temp);
}

void Raytracing::parse_light() {
  double x, y, z, cr, cg, cb;
  input_file >> x >> y >> z >> cr >> cg >> cb;
  auto *temp = new Light({x, y, z}, cr, cg, cb);
  lights.push_back(temp);
}

void Raytracing::parse_input_file() {
  input_file >> lor >> width >> total_objects;
  string cd;
  int i = total_objects;
  while (i--) {
    input_file >> cd;
    cout << "command: " << cd << endl;
    COMMAND command = Command::generate_command(cd);
    if(command == INVALID) break;
    parse_command(command);
  }
  input_file >> total_lights;

  i = total_lights;
  while (i--) {
    parse_light();
  }
  // floor
  addFloor();
}

Raytracing::Raytracing(): fovY{120}, aspect{1}, z_near{1}, z_far{3000.0} {
  input_file_name = "../test-cases/1/scene.txt";
  input_file.open(input_file_name);
  parse_input_file();
  image = new bitmap_image(width, width);
}

Raytracing::~Raytracing() {
  delete image;
  for(auto &obj: objects) {
    delete obj;
  }
  for(auto &light: lights) {
    delete light;
  }
  input_file.close();
}

void Raytracing::print_inputs() {
  cout << "Level of Recursion: " << lor << endl;
  cout << "Dimensions: " << width << "x" << width << endl;
  cout << endl << "Total objects: " << total_objects << endl;
  for(auto &obj: objects) {
    cout << endl;
    obj->printShape();
  }
  printf("Total light sources: %d\n", total_lights);
  for(auto &light: lights) {
    cout << endl;
    light->printLight();
  }
}

void Raytracing::addFloor() {
  Shape *temp = new Floor(1000, 20, 1, 1, 1);
  temp->setColor(0, 0, 0);
  temp->setCoefficients(.25, .25, .25, .25);
  temp->shine = 5;

  objects.push_back(temp);
}

void Raytracing::drawObjects() {

  for(auto &obj: objects) {
    if (obj->shapeName != "General") {
      obj->draw();
    }
  }
  for(auto &light: lights) {
    light->draw();
  }
}

void Raytracing::capture(const CameraHandler &ch) {
  auto i_width = width;

  printf("Capturing started\n");
  image->clear();
  auto planeDistance = (width / 2.0) / tan(fovY / 2 * pi / 180);
  auto top_left = ch.position + ch.look * planeDistance - ch.right * (width / 2) + ch.up * (width / 2);

  auto du = width / i_width;
  auto dv = width / i_width;

  top_left = top_left + ch.right * (0.5 * du) - ch.up * (0.5 * dv);

  for(int i = 1; i <= i_width; i++) {
    for(int j = 1; j <= i_width; j++) {
      auto cur_pixel = top_left + ch.right * du * i - ch.up * dv * j;
      auto dir = cur_pixel - ch.position;
      dir = dir.normalize();
      Ray ray(ch.position, dir);
      auto *color = new double[3];
      auto *dummy_color = new double[3];
      double min_pos_t = 1e9;
      Shape *closest_shape;
      for(auto &obj: objects) {
        auto t = obj->intersect(ray, dummy_color, 0, lights, objects);
        if(t > 0 && t < min_pos_t) {
          min_pos_t = t;
          closest_shape = obj;
        }
      }
      if(min_pos_t != 1e9) {
        closest_shape->intersect(ray, color, 3, lights, objects);
        image->set_pixel(i, j,color[0] * 255, color[1] * 255, color[2] * 255);
      }
      delete [] dummy_color;
      delete [] color;
    }
  }
  printf("Capturing done\n");
  image->save_image("output/output.bmp");
}

