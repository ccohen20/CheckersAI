//
//  Pieces.hpp
//  
//
//  Created by Robinson Lamont on 4/11/18.
//

#ifndef Pieces_hpp
#define Pieces_hpp

#include <stdio.h>

class Piece {
    private:
        char Color;
        int isKing;
        
        int xTile;
        int yTile;
    
    public:
        Piece(char Color, int xTile, int yTile);
        void makeKing();
        int isKing(){return this->isKing;}
        char getColor(){return this->Color;}
        int getX(){return this->xTile;}
        int getY(){return this->yTile;}
};

#endif /* Pieces_hpp */
