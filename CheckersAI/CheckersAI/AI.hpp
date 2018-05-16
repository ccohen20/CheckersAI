#ifndef AI_H
#define AI_H

#include "Board.hpp"
#include <cstdlib>

typedef struct m {
    int oldX;
    int oldY;
    int newX;
    int newY;
} Move;

Move makeMove(Board board);
int getMoveRec(Board board, int depth, int side);
vector<Move> getMoves(Board board, int side);
int scoreBoard(Board board, int side);
int together(Board board, int x, int y, int side);

#endif