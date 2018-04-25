#ifndef BOARDIMG_H
#define BOARDIMG_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void init(int argc, char ** argv);
void reshape(int newWidth, int newHeight);
void display(void);
void update();
void render();


#endif