//
//  Global.h
//  CheckersAI
//
//  Created by Kenny Wang on 4/12/18.
//  Copyright © 2018 Kenny Wang. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp


#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using namespace std;

const int BOARD_LENGTH = 8;

enum Piece {
    EMPTY,
    WHITE, WHITE_KING,
    BLACK, BLACK_KING
};

typedef struct PIECE {
	int isBlack;
	//using namespace std;
	vector<array<int, 2> > moves;
	int isKing;
	int pos[2];
}PIECE;

#endif /* Global_h */
