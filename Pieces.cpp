//
//  Pieces.cpp
//  
//
//  Created by Robinson Lamont on 4/11/18.
//

#include "Pieces.hpp"

class Piece {
    char Color;
    int isKing;
    
    int xTile;
    int yTile;
    
public:
    void makePiece(char Color, int xTile, int yTile);
    void makeKing();
   
    int isKing(){
        return isKing;
    }
    
    char getColor(){
        return this.Color;
    }
    
    int getX(){
        return this.xTile;
    }
    
    int getY(){
        return this.yTile;
    }
}

void Piece::Piece (char Color, int xTile, int yTile){
    this.Color = Color;
    this.xTile = xTile;
    this.yTile = yTile;
    this.isKing = 0;
}

void Piece::makeKing () {
    this.isKing = 1;
}

void Piece::makePiece (char Color, int xTile, int yTile){
    this.Color = Color;
    this.xTile = xTile;
    this.yTile = yTile;
    this.isKing = 0;
}
