//
//  Board.h
//  CheckersAI
//
//  Created by Kenny Wang on 4/12/18.
//  Copyright © 2018 Kenny Wang. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include "Global.hpp"
#include <stdio.h>

class Board {
    
public:
    Board();
    Board copyBoard();
    int movePiece(int currentX, int currentY, int newX, int newY);
    void printBoard();
    Piece board[BOARD_LENGTH][BOARD_LENGTH];
    int getPiece(int x, int y);
    void printPiece(int x, int y);
    bool validMove(int currentX, int currentY, int newX, int newY);
    
private:
    void initializePieces();
};

#endif /* Board_h */
