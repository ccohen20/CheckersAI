/*
    BoardImg.cpp handles Rendering of Board

*/

#include "BoardImg.hpp"

int width = 500;
int height = 300;
float distance = 100;

void init(int argc, char ** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Checkers");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0f);

    glDisable(GL_LIGHTING);

}

void reshape(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    gluPerspective(40.0, aspect, 25.0, distance * distance);

}

void display(void){
    update();
    render();
}

void update() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(30.0, 0.0, 0.0, 0, 0, 0, 0.0, 1.0, 0.0);
}

void render() {
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(0.0, -10.0, -10.0);
        glVertex3f(0.0, -10.0, 10.0);
        glVertex3f(0.0, 10.0, 10.0);
        glVertex3f(0.0, 10.0, -10.0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char ** argv){
    init(argc, argv);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}