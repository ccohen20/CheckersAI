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
    
    //add in white pieces
    for (int i=0; i<BOARD_LENGTH; i+=2) {
        
        for (int j=0; j<3; j+=2) {
            newBoard[i][j] = WHITE;
        }
    }
    
    for (int i=1; i<BOARD_LENGTH; i+=2) {
        newBoard[i][1] = WHITE;
    }
    
    for (int i=1; i<BOARD_LENGTH; i+=2) {
        for (int j=5; j<BOARD_LENGTH; j+=2) {
            newBoard[i][j] = BLACK;
        }
    }
    
    for (int i=0; i<BOARD_LENGTH; i+=2) {
        newBoard[i][6] = BLACK;
    }
}

Board::Board() {
    
    for(int i=0; i<BOARD_LENGTH; i++) {
        for(int j=0; i<BOARD_LENGTH; j++) {
            
            newBoard[i][j] = EMPTY;
        }
    }
    initializePieces();
    
}

