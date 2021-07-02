//
// Created by tushar on 7/2/21.
//

#include "Floor.h"
#include "../../drawShape/DrawShape.h"
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

