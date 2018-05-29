/*
    BoardImg.cpp handles Rendering of Board

*/
#include "search.hpp"
#include "BoardImg.hpp"
#include <ctime>

int width = 900;
int height = 400;
float dist = 100;
Board board;
//holds user input
int pieceX = -1;
int pieceY = -1;
int destX = -1;
int destY = -1;
//used to determine whether or not the computer should move
bool compMove = false;
bool playerMove = true;
//handles player or computer going again, if they can
bool playerJump = false;
bool compJump = false;
static int jumpX = -1;
static int jumpY = -1;
//makes sure board is drawn before any passes start
bool first = true;

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

    //handles game ending
    vector<Move> playerMoves = getMoves(board, player);
    vector<Move> compMoves = getMoves(board, computer);
    if ((int)playerMoves.size() == 0) {
        printf("You lose :(\n");
        exit(0);
    }
    else if ((int)compMoves.size() == 0) {
        printf("You win!! :)\n");
        exit(0);
    }


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

    //ensures board is drawn before game starts
    if (!first) {
        //updates for player AI
        if (playerMove) {

            Move move;
            //handles case where computer is jumping again
            if (playerJump) {
                move = makeJump(board, jumpX, jumpY, player);
                playerJump = false;
            }
            //gets the computer's move
            else {
                move = makeMove(board, player);
            }

            //determines whether or not a move is a jump
            int isJump = abs(move.newX - move.oldX) - 1;

            //handles jumping
            if (isJump == 1) {
                //handles first part of jump
                jumpAnimation(move.oldX, move.oldY, move.newX, move.newY, scale);

                //moves piece
                board.movePiece(move.oldX, move.oldY, move.newX, move.newY);

                //handles rest of animation
                int oppX = ((move.newX - move.oldX) / 2) + move.oldX;
                int oppY = ((move.newY - move.oldY) / 2) + move.oldY;
                moveAnimation(oppX, oppY, move.newX, move.newY, scale);

                //handles if the computer can jump again
                //gets the potential jumps for the comp
                vector<Move> playerJumps = getJumps(board, move.newX, move.newY);

                //if the comp can make a jump, it is still their turn, and they have to jump
                if ((int)playerJumps.size() != 0) {
                    playerJump = true;
                    jumpX = move.newX;
                    jumpY = move.newY;
                    compMove = false;
                }
            }
            //handles regular move
            else {
                board.movePiece(move.oldX, move.oldY, move.newX, move.newY);

                moveAnimation(move.oldX, move.oldY, move.newX, move.newY, scale);
            }

            //make sure comp doesn't move again
            if (!playerJump) {
                playerMove = false;
                compMove = true;
            }
        }
        //handles computer turn
        if (compMove) {

            Move move;
            //handles case where computer is jumping again
            if (compJump) {
                move = searchJump(board, d, jumpX, jumpY);
                compJump = false;
            }
            //gets the computer's move
            else {

                move = search(board, d, computer);
            }

            //determines whether or not a move is a jump
            int isJump = abs(move.newX - move.oldX) - 1;

            //handles jumping
            if (isJump == 1) {
                //handles first part of jump
                jumpAnimation(move.oldX, move.oldY, move.newX, move.newY, scale);

                //moves piece
                board.movePiece(move.oldX, move.oldY, move.newX, move.newY);

                //handles rest of animation
                int oppX = ((move.newX - move.oldX) / 2) + move.oldX;
                int oppY = ((move.newY - move.oldY) / 2) + move.oldY;
                moveAnimation(oppX, oppY, move.newX, move.newY, scale);

                //handles if the computer can jump again
                //gets the potential jumps for the comp
                vector<Move> compJumps = getJumps(board, move.newX, move.newY);

                //if the comp can make a jump, it is still their turn, and they have to jump
                if ((int)compJumps.size() != 0) {
                    compJump = true;
                    jumpX = move.newX;
                    jumpY = move.newY;
                    playerMove = false;
                }
            }
            //handles regular move
            else {
                board.movePiece(move.oldX, move.oldY, move.newX, move.newY);
                moveAnimation(move.oldX, move.oldY, move.newX, move.newY, scale);
            }

            //make sure comp doesn't move again
            if (!compJump) {
                compMove = false;
                playerMove = true;
            }
        }
    }
    first = false;

    glutPostRedisplay();

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
        for (int j = 7; j > -1; j--) {
            if (board.getPiece(i, j) != EMPTY && (x != i || y != j)) {
                int piece = board.getPiece(i, j);
                if (piece == BLACK || piece == BLACK_KING) {
                    glColor4f(0.0, 1.0, 0.0, 1.0);
                }
                else {
                    glColor4f(0.0, 0.0, 1.0, 1.0);
                }

                int h = 4;
                if (board.getPiece(i, j) == WHITE_KING || board.getPiece(i, j) == BLACK_KING) {
                    h = 8;
                }
                drawPiece(i, j, h, scale);
            }
        }
    }
}


//draws a given piece at (x, y) with color (r, g, b)
//scale used to map to correct place on board
void drawPiece(float x, float y, int h, float scale) {

    //updates x and y to reflect that of board
    x = 7 - x;

    //draws clyinder
    float w = 8;
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

        //draws pieces on board
        drawPieces(newX, newY, scale);

        //gets color
        //since we call animation after updating the board, we use the new postion for color
        int piece = board.getPiece(newX, newY);
        if (piece == BLACK || piece == BLACK_KING) {
            glColor4f(0.0, 1.0, 0.0, 1.0);
        }
        else {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }

        //handles king / regular height
        if (piece == WHITE || piece == BLACK) {
            drawPiece(X, Y, 4, scale);
        }
        else {
            drawPiece(X, Y, 8, scale);
        }

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

        //called before we update board, so don't draw piece where it used to be
        drawPieces(oldX, oldY, scale);

        //gets color
        //since we call animation before updating the board, we use the old postion for color
        int piece = board.getPiece(oldX, oldY);
        if (piece == BLACK || piece == BLACK_KING) {
            glColor4f(0.0, 1.0, 0.0, 1.0);
        }
        else {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }


        int h = 4;
        if (piece == BLACK_KING || piece == WHITE_KING) {
            h = 8;
        }
        //accounts for vertical jump
        glPushMatrix();
        glTranslatef(0.0,  10 * sin(t), 0.0);
        drawPiece(X, Y, h, scale);
        glPopMatrix();

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
    glutMainLoop();

    printf("exited");
    return 0;
}
