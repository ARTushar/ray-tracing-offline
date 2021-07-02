//
// Created by tushar on 7/1/21.
//

#ifndef RAYTRACING_OPENGL_H
#define RAYTRACING_OPENGL_H


#include "../utils/cameraHandler/CameraHandler.h"
#include "../raytracing/Raytracing.h"

class Opengl {
private:
    static void drawAxes();
    static void keyboardListener(unsigned char key, int x, int y);
    static void specialKeyListener(int key, int x,int y);
    static void mouseListener(int button, int state, int x, int y); //x, y is the x-y of the screen (2D)
    static void display();
    static void animate();
    static void init();
public:
    static Raytracing rt;
    static int drawaxes;
    static void draw(int argc, char **argv);
};


#endif //RAYTRACING_OPENGL_H
