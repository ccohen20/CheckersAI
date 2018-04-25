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

//constructor
//creates empty board and the puts pieces in correct positions
Board::Board() {
    for(int i=0; i<BOARD_LENGTH; i++) {
        for(int j=0; i<BOARD_LENGTH; j++) {
            
            board[i][j] = Piece::EMPTY;
        }
    }
    initializePieces();
    
}

