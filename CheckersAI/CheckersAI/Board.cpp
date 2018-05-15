//
//  Board.cpp
//  CheckersAI
//
//  Created by Kenny Wang on 4/12/18.
//  Copyright © 2018 Kenny Wang. All rights reserved.
//

#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>

//constructors
//creates empty board and the puts pieces in correct positions
Board::Board() {
    for(int i=0; i<BOARD_LENGTH; i++) {
        for(int j=0; j<BOARD_LENGTH; j++) {
            
            board[i][j] = EMPTY;
        }
    }
    initializePieces();
}

void Board::initializePieces() {
    
    //adds in white pieces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = WHITE;
            }
        }
    }
    
    //adds black pieces
    for (int i = BOARD_LENGTH - 1; i > BOARD_LENGTH - 4; i--) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = BLACK;
            }
        }
    }
}

//moves piece from specified tile to specified tile
int Board::movePiece(int currentX, int currentY, int newX, int newY) {
    //if empty piece is on the tile, we don't want to do anything (maybe throw an error?)
    if (board[currentY][currentX] == EMPTY) {
        printf("Invlaid Move: No piece at (%i, %i)\n", currentX, currentY);
        return 1;
    }
    //if the move is not valid, we don't want to do anything (maybe throw an error?)
    else if (!validMove(currentX, currentY, newX, newY)) {
        printf("Invalid Move: Cannot move piece from (%i, %i) to (%i, %i)\n", currentX, currentY, newX, newY);
        return 1;
    }
    //otherwise, the move is valid, and we update board
    else {
        board[newY][newX] = board[currentY][currentX];
        board[currentY][currentX] = EMPTY;

        short isJump = abs(newX - currentX) - 1;
        //removes jumped piece if the move is a jump
        if (isJump == 1) {
            int changeX;
            int changeY;
            //handles change in X
            if (newX - currentX > 0) {
                changeX = 1;
            }
            else {
                changeX = -1;
            }
            //handles change in Y
            if (newY - currentY > 0) {
                changeY = 1;
            }
            else {
                changeY = -1;
            }

            int oppX = currentX + changeX;
            int oppY = currentY + changeY;

            board[oppY][oppX] = EMPTY;
        }

        //kings a piece if it got to the end
        if (board[newY][newX] == WHITE && newY == 7) {
            board[newY][newX] = WHITE_KING;
        }
        else if (board[newY][newX] == BLACK && newY == 0) {
            board[newY][newX] = BLACK_KING;
        }
        return 0;
    }
}

//prints the current board, used for debugging
void Board::printBoard() {
    printf("   0 1 2 3 4 5 6 7\n");
    printf("   ---------------\n");
    for (int i = 0; i < BOARD_LENGTH; i++) {
        printf("%i: ", i);
        for (int j = 0; j < BOARD_LENGTH; j++) {
            printf("%i ", board[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


//checks if a given move is valid
//returns 0 on valid, 1 on square occupied, and 2 on move/direction not allowed
bool Board::validMove(int currentX, int currentY, int newX, int newY) {
    
    //stores value for simplicity
    Piece piece = board[currentY][currentX];

    //if a piece is on the passed destination, cannot move there
    if (board[newY][newX] != EMPTY) {
        return false;
    }

    //must move diagonally
    if (abs(newX - currentX) != abs(newY - currentY)) {
        return false;
    }

    //stores direction of piece
    int dir = newY - currentY;

    //stores values for opposite player
    Piece opp;
    Piece oppKing;
    if (piece == WHITE || piece == WHITE_KING) {
        opp = BLACK;
        oppKing = BLACK_KING;
    }
    else {
        opp = WHITE;
        oppKing = WHITE_KING;
    }

    //determines whether or not the attempted move is a jump
    //when moving 2 tiles away, so when abs(newX - currentX) == 2
    short isJump = abs(newX - currentX) - 1;

    //printf("%i\n", isJump);

    //if jump is greather than 1, invalid move
    if (isJump > 1) {
        return false;
    }

    //if jumping, finds whether or not there is an opposing piece in between the current piece and the destination
    if (isJump == 1) {
        int changeX;
        int changeY;
        //handles change in X
        if (newX - currentX > 0) {
            changeX = 1;
        }
        else {
            changeX = -1;
        }
        //handles change in Y
        if (newY - currentY > 0) {
            changeY = 1;
        }
        else {
            changeY = -1;
        }

        int oppX = currentX + changeX;
        int oppY = currentY + changeY;
        //printf("Opp Position: (%i, %i)\n", oppX, oppY);
        //printf("Opp: %i, board[oppY][oppX]: %i\n", opp, board[oppY][oppX]);
        if (board[oppY][oppX] != opp && board[oppY][oppX] != oppKing) {
            return false;
        }
    }

    //handles kings
    //printf("Dir: %i\n", dir);
    if (piece == WHITE_KING || piece == BLACK_KING) {
        //already checked for valid jump, if jump, and already checked
        //for moving in a diagonal
        return true;
    }
    //handles black pieces
    else if (piece == BLACK) {
        //only move forward
        if (dir < 0) {
            return true;
        }
        else {
            return false;
        }
    }
    //handles white pieces
    else if (piece == WHITE) {
        //only move forward
        if (dir > 0) {
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}


//debuging functions
//returns piece at (x, y)
int Board::getPiece(int x, int y) {
    return board[y][x];
}

//prints piece at (x, y)
void Board::printPiece(int x, int y) {
    printf("%i\n", board[y][x]);
}