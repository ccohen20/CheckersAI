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
        for(int j=0; i<BOARD_LENGTH; j++) {
            
            board[i][j] = Piece::EMPTY;
        }
    }
    initializePieces();
}

void Board::initializePieces() {
    
    //adds in white pieces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = Piece::WHITE;
            }
        }
    }

    /* Old add in white pieces (discuss this)
    for (int i=0; i<BOARD_LENGTH; i+=2) {
        
        for (int j=0; j<3; j+=2) {
            board[i][j] = WHITE;
        }
    }
    
    for (int i=1; i<BOARD_LENGTH; i+=2) {
        board[i][1] = WHITE;
    }*/
    
    //adds black pieces
    for (int i = BOARD_LENGTH - 1; i > BOARD_LENGTH - 4; i--) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = Piece::BLACK;
            }
        }
    }

    /* old add black pieces (dicsuss this)
    for (int i=1; i<BOARD_LENGTH; i+=2) {
        for (int j=5; j<BOARD_LENGTH; j+=2) {
            board[i][j] = BLACK;
        }
    }
    
    for (int i=0; i<BOARD_LENGTH; i+=2) {
        board[i][6] = BLACK;
    }*/
}

//moves piece from specified tile to specified tile
void Board::movePiece(int currentX, int currentY, int newX, int newY) {
    //if empty piece is on the tile, we don't want to do anything (maybe throw an error?)
    if (board[currentX][currentY] == Piece::EMPTY) {

    }
    //if the move is not valid, we don't want to do anything (maybe throw an error?)
    else if (!validMove(currentX, currentY, newX, newY)) {

    }
    //otherwise, the move is valid, and we update board
    else {
        board[newX][newY] = board[currentX][currentY];
        board[currentX][currentY] = Piece::EMPTY;
    }
}

//checks if a given move is valid
//returns 0 on valid, 1 on square occupied, and 2 on move/direction not allowed
bool Board::validMove(int currentX, int currentY, int newX, int newY) {
    
    //stores value for simplicity
    Piece piece = board[currentX][currentY];

    //if a piece is on the passed destination, cannot move there
    if (board[newX][newY] != Piece::EMPTY) {
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
    if (piece == Piece::WHITE || piece == Piece::WHITE_KING) {
        opp = Piece::BLACK;
        oppKing = Piece::BLACK_KING;
    }
    else {
        opp = Piece::WHITE;
        oppKing = Piece::WHITE_KING;
    }

    //determines whether or not the attempted move is a jump
    //when moving 2 tiles away, so when abs(newX - currentX) == 2
    short isJump = abs(newX - currentX) - 1;

    //if jump is greather than 1, invalid move
    if (isJump > 1) {
        return false;
    }

    //if jumping, finds whether or not there is an opposing piece in between the current piece and the destination
    if (isJump == 1) {
        int changeX = newX - currentX;
        int changeY = newY - currentY;
        int oppX = currentX + changeX;
        int oppY = currentY + changeY;
        if (board[oppX][oppY] != opp || board[oppX][oppY] != oppKing) {
            return false;
        }
    }

    //handles kings
    if (piece == Piece::WHITE_KING || piece == Piece::BLACK_KING) {
        //already checked for valid jump, if jump, and already checked
        //for moving in a diagonal
        return true;
    }
    //handles black pieces
    else if (piece == Piece::BLACK || piece == Piece::BLACK_KING) {
        //only move forward
        if (dir > 0) {
            return true;
        }
        else {
            return false;
        }
    }
    //handles white pieces
    else if (piece == Piece::WHITE) {
        //only move forward
        if (dir > 0) {
            return true;
        }
        else {
            return false;
        }
    }
}