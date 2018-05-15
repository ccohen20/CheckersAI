//
//  Board.h
//  CheckersAI
//
//  Kenny Wang, Cam Cohen, Robby Lamon
//  
//

#ifndef Board_hpp
#define Board_hpp

#include "Global.hpp"
#include <stdio.h>

class Board {
    
public:
    Board();
    int movePiece(int currentX, int currentY, int newX, int newY);
    void printBoard();
    Piece board[BOARD_LENGTH][BOARD_LENGTH];
    int getPiece(int x, int y);
    void printPiece(int x, int y);
    
private:
    void initializePieces();
    bool validMove(int currentX, int currentY, int newX, int newY);
};

#endif /* Board_h */
