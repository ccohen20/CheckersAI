#ifndef BOARDIMG_H
#define BOARDIMG_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <string>
#include <cctype>
#include "Board.hpp"
using namespace std;

void init(int argc, char ** argv);
void reshape(int newWidth, int newHeight);
void display(void);
void update();
void render();
void drawBoard(float scale);
void drawPieces(int x, int y, float scale);
void drawPiece(float x, float y, float scale);
void moveAnimation(int oldX, int oldY, int newX, int newY, float scale);


#endif