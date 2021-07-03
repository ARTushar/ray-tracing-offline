#include "opengl/Opengl.h"
#include "raytracing/Raytracing.h"
#include "utils/drawShape/DrawShape.h"
#include "utils/shape/sphere/Sphere.h"
#include "utils/shape/floor/Floor.h"
#include <GL/glut.h>

CameraHandler ch;
Raytracing rt;
int drawaxes;


void specialKeyListener(int key, int x, int y) {
  switch(key){
    case GLUT_KEY_DOWN:		//down arrow key
      ch.move_backward();
      break;
    case GLUT_KEY_UP:		// up arrow key
      ch.move_forward();
      break;
    case GLUT_KEY_RIGHT:
      ch.move_right();
      break;
    case GLUT_KEY_LEFT:
      ch.move_left();
      break;
    case GLUT_KEY_PAGE_UP:
      ch.move_up();
      break;
    case GLUT_KEY_PAGE_DOWN:
      ch.move_down();
      break;

    case GLUT_KEY_INSERT:
      break;

    case GLUT_KEY_HOME:
      break;
    case GLUT_KEY_END:
      break;

    default:
      break;
  }
}

void keyboardListener(unsigned char key, int x, int y) {
  switch(key){
    case '1':
      ch.look_left();
      break;
    case '2':
      ch.look_right();
      break;
    case '3':
      ch.look_up();
      break;
    case '4':
      ch.look_down();
      break;
    case '5':
      ch.tilt_c();
      break;
    case '6':
      ch.tilt_cc();
      break;
    case '0':
      rt.capture(ch);
      break;
    default:
      break;
  }

}

void drawAxes() {
  if(drawaxes==1)
  {
    DrawShape::drawAxes(2000);
  }
}

void mouseListener(int button, int state, int x, int y) {
  switch(button){
    case GLUT_LEFT_BUTTON:
      if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
      }
      break;

    case GLUT_RIGHT_BUTTON:
      if(state == GLUT_DOWN) {
        drawaxes=1-drawaxes;
      }
      break;

    case GLUT_MIDDLE_BUTTON:
      //........
      break;

    default:
      break;
  }
}

void display() {
  //clear the display
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0,0,0,0);	//color black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /********************
  / set-up camera here
  ********************/
  //load the correct matrix -- MODEL-VIEW matrix
  glMatrixMode(GL_MODELVIEW);

  //initialize the matrix
  glLoadIdentity();

  //now give three info
  //1. where is the camera (viewer)?
  //2. where is the camera looking?
  //3. Which direction is the camera's UP direction?

  gluLookAt(ch.get_posx(), ch.get_posy(), ch.get_posz(),
            ch.get_lookx(), ch.get_looky(), ch.get_lookz(),
            ch.get_upx(), ch.get_upy(), ch.get_upz());

  //again select MODEL-VIEW
  glMatrixMode(GL_MODELVIEW);

  /****************************
  / Add your objects from here
  ****************************/
  //add objects

//  drawAxes();
  rt.drawObjects();
//  DrawShape::drawTile({0, 0, 0}, 100);
  //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
  glutSwapBuffers();
}

void animate() {
  //codes for any changes in Models, Camera
  glutPostRedisplay();
}

void init() {
  //codes for initialization
  drawaxes=1;
  //clear the screen
  glClearColor(0,0,0,0);

  /************************
  / set-up projection here
  ************************/
  //load the PROJECTION matrix
  glMatrixMode(GL_PROJECTION);

  //initialize the matrix
  glLoadIdentity();

  //give PERSPECTIVE parameters
  gluPerspective(rt.fovY,	rt.aspect,	rt.z_near,	rt.z_far);
  //field of view in the Y (vertically)
  //aspect ratio that determines the field of view in the X direction (horizontally)
  //near distance
  //far distance
}

void draw(int argc, char **argv) {
  glutInit(&argc,argv);
  glutInitWindowSize(rt.width, rt.width);
  glutInitWindowPosition(0, 0);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

  glutCreateWindow("Tushar's OpenGL Program");

  init();

  glEnable(GL_DEPTH_TEST);	//enable Depth Testing

  glutDisplayFunc(display);	//display callback function
  glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

  glutKeyboardFunc(keyboardListener);
  glutSpecialFunc(specialKeyListener);
  glutMouseFunc(mouseListener);

  glutMainLoop();		//The main loop of OpenGL

}


int main(int argc, char **argv) {
  draw(argc, argv);
//  Sphere::test();
//    Floor::test();
}