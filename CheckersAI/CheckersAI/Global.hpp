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

typedef struct MOVE {
    //int isBlack;
    //int isKing;
    int score;
    int start[2];
    int dest[2];
}MOVE;

typedef struct PIECE {
	int isBlack;
	//using namespace std;
    vector<MOVE> moves;
	int isKing;
	int pos[2];
    int maxScore;
    int maxIndex;
public:
    void setPos(int, int);
    void addMove(int, int);
    void clearMoves();
    MOVE getMove(int);
    int getSize();
    int getX();
    int getY();
    void genScore();
}PIECE;

void PIECE:genScore(){
    int size = moves.size();
    if(size>0){
        int ind = 0;
        int max = moves[0].score;
        for(int i = 1; i < size; i++){
            if(moves[i].score>max){
                max = moves[i].score;
                ind = i;
            }
            }
        maxScore = max;
        maxIndex = ind;
    } else {
        maxScore = 0;
        maxIndex = 0;
    }
    
}

int PIECE::getX(){
    return pos[0];
}

int PIECE::getY(){
    return pos[1];
}

MOVE PIECE::getMove(int index){
    return moves[index];
}

int PIECE::getSize(){
    return moves.size();
}

void PIECE::setPos(int x, int y){
    pos[0] = x;
    pos[1] = y;
    return;
    
}

void PIECE::addMove(int x, int y){
    MOVE move;
    move.dest[0] = x;
    move.dest[1] = y;
    moves.push_back(move);
    return;
}

void PIECE::clearMoves(){
    vector<MOVE> moves2;
    moves = moves2;
    return;
}

#endif /* Global_h */
