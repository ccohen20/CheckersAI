#include "AI.hpp"

const int player = 0;
const int computer = 1;

//gets the best move from a given board state
int getMove(Board board, int depth) {
    //base case
    if (depth == 0) {
        return scoreBoard(board);
    }
    else {
        //gets the players moves
        getMoves(board, player);
    }
    
}


//gets the potential moves
vector<Move> getMoves(Board board, int side) {

    //stores moves
    vector<Move> valid;

    //gets which side to check for
    int piece;
    int king;
    if (side == player) {
        piece = BLACK;
        king = BLACK_KING;
    }
    else {
        piece = WHITE;
        king = WHITE_KING;
    }

    //finds valid moves for each piece
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            int p = board.getPiece(i, j);

            //if the piece matches the side we are examiniing
            if (p == piece || p == king) {
                int count = 0;
                Move potentialMoves[8];

                //initializes potential moves
                //initializes one square away
                for (int k = -1; k < 2; k += 2) {
                    for (int l = -1; l < 2; l += 2) {
                        Move move;
                        move.oldX = i;
                        move.oldY = j;
                        move.newX = i + k;
                        move.newY = j + l;
                        potentialMoves[count] = move;

                        count++;
                    }
                }

                //initializes jumps
                for (int k = -2; k < 3; k += 4) {
                    for (int l = -2; l < 3; l += 4) {
                        Move move;
                        move.oldX = i;
                        move.oldY = j;
                        move.newX = i + k;
                        move.newY = j + l;
                        potentialMoves[count] = move;

                        count++;
                    }
                }

                //determines valid moves and adds them to valid
                for (int i = 0; i < 8; i++) {
                    if (board.validMove(potentialMoves[i].oldX, potentialMoves[i].oldY, potentialMoves[i].newX, potentialMoves[i].newY)) {
                        valid.push_back(potentialMoves[i]);
                    }
                }


            }
        }
    }

    return valid;
}

//scores a given board
int scoreBoard(Board board) {

}



