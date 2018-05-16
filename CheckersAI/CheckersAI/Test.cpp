//#include "Board.hpp"
//#include "BoardImg.hpp"
#include "AI.hpp"

int main() {
    /*//tests board
    Board board;

    //test printboard
    board.printBoard();

    //invalid moves (non diagonal)
    printf("Invalid Moves: non diagaonal\n");
    board.movePiece(6, 2, 6, 3);
    board.movePiece(6, 2, 5, 2);
    board.movePiece(6, 2, 7, 2);
    board.movePiece(6, 2, 6, 1);
    printf("\n");
    
    //invalid moves (not 45 degree diagonal)
    printf("Invalid Moves: non - 45 diagonal\n");
    board.movePiece(6, 2, 7, 4);
    board.movePiece(6, 2, 5, 4);
    printf("\n");

    //valid moves
    board.movePiece(1, 5, 0, 4);
    board.movePiece(2, 2, 1, 3);
    //invalid move - tests collision of pieces
    printf("Invalid Move: Collision of pieces\n");
    board.movePiece(0, 4, 1, 3);
    printf("\n");
    //valid jump
    board.movePiece(0, 4, 2, 2);

    board.movePiece(6, 2, 5, 3);
    //invalid move - backwards non-king
    printf("Invalid Move: Backwards for non-king\n");
    board.movePiece(5, 3, 6, 2);
    board.movePiece(2, 2, 1, 3);
    printf("\n");

    //test for kinging pieces
    board.movePiece(1, 1, 3, 3);
    board.movePiece(3, 3, 4, 4);
    board.movePiece(0, 0, 1, 1);
    board.movePiece(1, 1, 2, 2);
    board.movePiece(5, 5, 3, 3);
    board.movePiece(3, 3, 1, 1);
    board.printBoard();
    board.movePiece(1, 1, 0, 0);

    board.printBoard();

    //tests moving kings
    board.movePiece(0, 0, 1, 1);

    //tests jumping with kings
    board.movePiece(3, 1, 2, 2);
    board.movePiece(1, 1, 3, 3);

    //gets white king
    board.movePiece(0, 6, 1, 5);
    board.movePiece(1, 5, 0, 4);
    board.movePiece(1, 7, 0, 6);
    board.movePiece(0, 6, 1, 5);
    board.movePiece(4, 2, 2, 4);
    board.movePiece(2, 4, 0, 6);

    board.printBoard();

    board.movePiece(0, 6, 1, 7);

    //tests moving white king
    board.movePiece(1, 7, 0, 6);
    

    board.printBoard();*/

    Board board;
    
    board.printBoard();

    vector<Move> moves = getMoves(board, 0);
    printf("%lu\n", moves.size());

    //test getMove
    for (int i = 0; i < (int)moves.size(); i++) {
        Move move = moves[i];
        printf("From: %i, %i\nTo: %i, %i\n", move.oldX, move.oldY, move.newX, move.newY);
    }

    //testsHelper
    int val = getMoveRec(board, 3, 0);
    printf("Val: %i\n", val);

    //tests makeMove
    makeMove(board);

    board.printBoard();



}