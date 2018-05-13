#ifndef BOARDIMG_H
#define BOARDIMG_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>

void init(int argc, char ** argv);
void reshape(int newWidth, int newHeight);
void display(void);
void update();
void render();
void drawBoard(float scale);
void drawPiece(float x, float y, float scale, double r, double g, double b);
void moveAnimation(int oldX, int oldY, int newX, int newY, float scale);


#endif