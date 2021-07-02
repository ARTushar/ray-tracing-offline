//
// Created by tushar on 7/2/21.
//

#ifndef RAYTRACING_RAYTRACING_H
#define RAYTRACING_RAYTRACING_H


#include <iostream>
#include <fstream>
#include <vector>
#include "../utils/command/Command.h"
#include "../utils/shape/Shape.h"
#include "../utils/light/Light.h"

using namespace std;

class Raytracing {
public:
    int lor, total_objects, total_lights;
    double width;
    static bool DEBUG;
private:
    vector<Shape*> objects;
    vector<Light*> lights;
    std::string input_file_name;
    std::ifstream input_file;
    void parse_command(const COMMAND &command);
    void parse_triangle();
    void parse_sphere();
    void parse_general();
    void parse_light();
    void addFloor();
public:
    Raytracing();
    void drawObjects();
    void parse_input_file();
    void print_inputs();
    virtual ~Raytracing();
};


#endif //RAYTRACING_RAYTRACING_H
