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
    
protected:
    Piece board[BOARD_LENGTH][BOARD_LENGTH];
    void initializePieces();
    
};

#endif /* Board_h */
