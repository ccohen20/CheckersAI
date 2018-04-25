//
//  Pieces.cpp
//  
//
//  Created by Robinson Lamont on 4/11/18.
//

#include "Pieces.hpp"

Piece::Piece (char Color, int xTile, int yTile){
    this->Color = Color;
    this->xTile = xTile;
    this->yTile = yTile;
    this->isKing = 0;
}

void Piece::makeKing () {
    this->isKing = 1;
}
