//
// Created by tushar on 7/2/21.
//

#include "Raytracing.h"
#include "../utils/shape/sphere/Sphere.h"
#include "../utils/shape/general/General.h"
#include "../utils/shape/triangle/Triangle.h"
#include "../utils/shape/floor/Floor.h"


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

Raytracing::Raytracing() {
  input_file_name = "../test-cases/1/scene.txt";
  input_file.open(input_file_name);
  parse_input_file();
}

Raytracing::~Raytracing() {
  input_file.close();
}

void Raytracing::print_inputs() {
  cout << "Level of Recursion: " << lor << endl;
  cout << "Dimensions: " << width << "x" << width << endl;
  cout << endl << "Total objects: " << total_objects << endl;
  for(auto obj: objects) {
    cout << endl;
    obj->printShape();
  }
  printf("Total light sources: %d\n", total_lights);
  for(auto light: lights) {
    cout << endl;
    light->printLight();
  }
}

void Raytracing::addFloor() {
  Shape *temp = new Floor(1000, 20, 1, 1, 1);
  temp->setColor(0, 0, 0);
  temp->setCoefficients(.6, .2, .1, .1);
  temp->shine = 5;

  objects.push_back(temp);
}

void Raytracing::drawObjects() {

  for(auto obj: objects) {
    if (obj->shapeName != "General") {
      obj->draw();
    }
  }
}

