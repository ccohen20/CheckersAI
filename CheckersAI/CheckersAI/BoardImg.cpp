/*
    BoardImg.cpp handles Rendering of Board

*/

#include "BoardImg.hpp"

int width = 900;
int height = 400;
float dist = 100;
Board board;
//holds user input
int pieceX = -1;
int pieceY = -1;
int destX = -1;
int destY = -1;

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

    //updates board
    if (pieceX != -1 && pieceY != -1 && destX != -1 && destY != -1) {
        int isJump = destX - pieceX - 1;
        if (isJump > 1) {
            printf("Invalid Move: Cannot jump that far\n");
        }
        else if (isJump == 1) {
            jumpAnimation(pieceX, pieceY, destX, destY, scale);
        }

        board.movePiece(pieceX, pieceY, destX, destY);

        if (isJump == 1) {
            int oppX = ((destX - pieceX) / 2) + pieceX;
            int oppY = ((destY - pieceY) / 2) + pieceY;
            moveAnimation(oppX, oppY, destX, destY, scale);
        }
        else {
            moveAnimation(pieceX, pieceY, destX, destY, scale);
        }

        pieceX = -1;
        pieceY = -1;
        destX = -1;
        destY = -1;
    }

    glutSwapBuffers();
}

//gets user input
void input() {
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
    glutPostRedisplay();
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
            if (board.getPiece(i, j) != EMPTY && (x != i || y != j)) {
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
    int steps = 100;
    //hold increment values for each iteration
    double rX = (float)(newX - oldX) / steps;
    double rY = (float)(newY - oldY) / steps;

    double X = oldX;
    double Y = oldY;

    //animation loop
    for (int i = 0; i < steps; i++) {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawBoard(scale);

        //gets color
        //since we call animation after updating the board, we use the new postion for color
        int piece = board.getPiece(newX, newY);
        if (piece == BLACK || piece == BLACK_KING) {
            glColor4f(0.0, 1.0, 0.0, 1.0);
        }
        else {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }

        drawPiece(X, Y, scale);

        drawPieces(newX, newY, scale);

        X = X + rX;
        Y = Y + rY;

        glutSwapBuffers();
    }

    //end of animation
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawBoard(scale);

    //gets color
    //since we call animation after updating the board, we use the new postion for color
    int piece = board.getPiece(newX, newY);
    if (piece == BLACK || piece == BLACK_KING) {
        glColor4f(0.0, 1.0, 0.0, 1.0);
    }
    else {
        glColor4f(0.0, 0.0, 1.0, 1.0);
    }

    drawPieces(-1, -1, scale);

    glutSwapBuffers();


}


//jump animation
//jumpAnimation for a piece
void jumpAnimation (int oldX, int oldY, int newX, int newY, float scale) {
    //used for iteration
    int steps = 100;

    //gets location of enemy piece
    int oppX = ((newX - oldX) / 2) + oldX;
    int oppY = ((newY - oldY) / 2) + oldY;

    //hold increment values for each iteration
    double rX = (float)(oppX - oldX) / steps;
    double rY = (float)(oppY - oldY) / steps;
    double tstep = M_PI / steps;

    //initial values
    double X = oldX;
    double Y = oldY;
    double t = 0;

    //animation loop for jumping onto piece
    for (int i = 0; i < steps; i++) {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        drawBoard(scale);

        //gets color
        //since we call animation after updating the board, we use the new postion for color
        int piece = board.getPiece(newX, newY);
        if (piece == BLACK || piece == BLACK_KING) {
            glColor4f(0.0, 1.0, 0.0, 1.0);
        }
        else {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }

        //accounts for vertical jump
        glPushMatrix();
        glTranslatef(0.0,  10 * sin(t), 0.0);;
        drawPiece(X, Y, scale);
        glPopMatrix();

        //called before we update board, so don't draw piece where it used to be
        drawPieces(oldX, oldY, scale);

        //increment values
        X = X + rX;
        Y = Y + rY;
        t = t + tstep;

        glutSwapBuffers();
    }
}


int main(int argc, char ** argv){
    init(argc, argv);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(input);
    glutMainLoop();

    printf("exited");
    return 0;
}