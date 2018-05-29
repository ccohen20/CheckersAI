#ifndef BOARDIMG_H
#define BOARDIMG_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include "Board.hpp"
#include "AI.hpp"
using namespace std;

void init(int argc, char ** argv);
void reshape(int newWidth, int newHeight);
void display(void);
void update();
void render();
void input();
void drawBoard(float scale);
void drawPieces(int x, int y, float scale);
void drawPiece(float x, float y, int h, float scale);
void moveAnimation(int oldX, int oldY, int newX, int newY, float scale);
void jumpAnimation(int oldX, int oldY, int newX, int newY, float scale);


#endif