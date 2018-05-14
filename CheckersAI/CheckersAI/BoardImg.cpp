/*
    BoardImg.cpp handles Rendering of Board

*/

#include "BoardImg.hpp"

int width = 900;
int height = 400;
float dist = 100;
Board board;

//called once at beginning
//initializes environment
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

//called when window is reshaped
void reshape(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    glViewport(0, 0, width, height);

    //realligns perspective projection transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    gluPerspective(40.0, aspect, 25.0, dist * dist);

}

//called every frame, divided into update and render
void display(void){
    update();
    render();
}

//updates any logic before rendering
    //includes moving pieces, and awarding king values
void update() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(70.0, 80.0, -80.0, 70.0, 0.0, 50.0, 0.0, 1.2, 1.0);
}

void render() {
    //holds scale of board
    float scale = 20.0;

    //draws board
    drawBoard(scale);

    //renders the pieces
    drawPieces(-1, -1, scale);

    //gets user input
    int pieceX = -1;
    int pieceY = -1;
    int destX = -1;
    int destY = -1;
    //handles selecting the piece
    bool done = false;
    while (!done) {
        string input;
        printf("Select a piece in the form row_column, where _ indicates a space: ");
        getline(cin, input);
        if (input.length() != 3) {
            printf("Invalid Input: Input must be of the form int_int where _ is a space\n");
        }
        else if (!isdigit(input[0]) || !isdigit(input[2])) {
            printf("Invalid Input: Input must be of the form int_int where _ is a space\n");
        }
        else {
            pieceX = input[0] - '0';
            pieceY = input[2] - '0';
            if (board.getPiece(pieceX, pieceY) != EMPTY) {
                done = true;
            }
            else {
                printf("Invalid Selection: Must select a tile your piece is on\n");
            }
        }
        cin.clear();
    }
    //handles selecting the destination
    done = false;
    while (!done) {
        string input;
        printf("Select a destination in the form row_column, where _ indicates a space: ");
        getline(cin, input);
        if (input.length() != 3) {
            printf("Invalid Input: Input must be of the form int_int where _ is a space\n");
        }
        else if (!isdigit(input[0]) || !isdigit(input[2])) {
            printf("Invalid Input: Input must be of the form int_int where _ is a space\n");
        }
        else {
            destX = input[0] - '0';
            destY = input[2] - '0';
            if (board.getPiece(destX, destY) == EMPTY) {
                done = true;
            }
            else {
                printf("Invalid Selection: Must select an empty tile\n");
            }
        }
        cin.clear();
    }

    //updates board
    board.movePiece(pieceX, pieceY, destX, destY);

    moveAnimation(pieceX, pieceY, destX, destY, scale);

    glutSwapBuffers();
}


//draws the board
void drawBoard(float scale) {
    //puts translation matrix on so we have offset
        //makes placing peices easier
    glPushMatrix();
    glTranslated(-10.0, 0.0, -10.0);

    //creates board
    int z; //goes through z coordinates
    int x; //goes through x coordinates
    for (z = 0; z < 8; z++) {
        for (x = 0; x < 8; x++) {
            //handles color
            if ((z + x) % 2 == 0)
                glColor4f(1.0, 0.0, 0.0, 1.0);
            else
                glColor4f(0.0, 0.0, 0.0, 1.0);

            glBegin(GL_QUADS);
                glVertex3f(x * scale, 0.0, z * scale);
                glVertex3f(x * scale + scale, 0.0, z * scale);
                glVertex3f(x * scale + scale, 0.0, z * scale + scale);
                glVertex3f(x * scale, 0.0, z * scale + scale);
            glEnd();
        }
    }

    glPopMatrix();

}


//draws all pieces on the board, except the piece at the passed position
void drawPieces(int x, int y, float scale) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getPiece(i, j) != EMPTY && x != i && y != j) {
                int piece = board.getPiece(i, j);
                if (piece == BLACK || piece == BLACK_KING) {
                    glColor4f(0.0, 1.0, 0.0, 1.0);
                }
                else {
                    glColor4f(0.0, 0.0, 1.0, 1.0);
                }

                drawPiece(i, j, scale);
            }
        }
    }
}


//draws a given piece at (x, y) with color (r, g, b)
//scale used to map to correct place on board
void drawPiece(float x, float y, float scale) {

    //updates x and y to reflect that of board
    x = 7 - x;

    //draws clyinder
    float w = 8;
    float h = 4;
    glPushMatrix();
    glTranslated(x * scale, 0, y * scale);

    //bases
    glBegin(GL_QUADS);
        glVertex3f(-w, 0.0, w);
        glVertex3f(-w, 0.0, -w);
        glVertex3f(w, 0.0, -w);
        glVertex3f(w, 0.0, w);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-w, h, w);
        glVertex3f(-w, h, -w);
        glVertex3f(w, h, -w);
        glVertex3f(w, h, w);
    glEnd();

    //sides
    glBegin(GL_QUADS);
        glVertex3f(-w, 0.0, w);
        glVertex3f(-w, 0.0, -w);
        glVertex3f(-w, h, -w);
        glVertex3f(-w, h, w);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(w, 0.0, w);
        glVertex3f(w, 0.0, -w);
        glVertex3f(w, h, -w);
        glVertex3f(w, h, w);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(w, 0.0, -w);
        glVertex3f(-w, 0.0, -w);
        glVertex3f(-w, h, -w);
        glVertex3f(w, h, -w);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(w, 0.0, w);
        glVertex3f(-w, 0.0, w);
        glVertex3f(-w, h, w);
        glVertex3f(w, h, w);
    glEnd();

    glPopMatrix();
}


//moveAnimation for a piece
void moveAnimation (int oldX, int oldY, int newX, int newY, float scale) {
    //used for iteration
    int steps = 1000;
    //hold increment values for each iteration
    double rX = (float)(newX - oldX) / steps;
    double rY = (float)(newY - oldY) / steps;

    double X = oldX;
    double Y = oldY;
    //animation loop
    for (int i = 0; i < steps; i++) {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawBoard(scale);

        //since we call animation after updating the board, we use the new postion for color
        int piece = board.getPiece(newX, newY);
        if (piece == BLACK || piece == BLACK_KING) {
            glColor4f(0.0, 1.0, 0.0, 1.0);
        }
        else {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }

        drawPiece(X, Y, scale);

        X = X + rX;
        Y = Y + rY;

        glutSwapBuffers();
    }
}

int main(int argc, char ** argv){
    init(argc, argv);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    printf("exited");
    return 0;
}