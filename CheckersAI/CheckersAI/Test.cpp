#include "Board.hpp"
#include "BoardImg.hpp"

int main() {
    //tests board
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
    

    board.printBoard();
}