#include "Board.hpp"
#include "BoardImg.hpp"

int main() {
    //tests board
    Board board;

    //test printboard
    board.printBoard();

    //invalid

    //valid moves
    board.movePiece(1, 5, 0, 4);
    board.movePiece(2, 2, 1, 3);
    //invalid move - tests collision of pieces
    board.movePiece(0, 4, 1, 3);
    //valid jump
    board.movePiece(0, 4, 2, 2);

    board.printBoard();
}