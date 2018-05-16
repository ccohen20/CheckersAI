#include "Board.hpp"
using namespace std;

int main(){

    /*
	PIECE test;
	test.pos[0] = 1 ;
	printf("%d\n", test.pos[0]);

    MOVE move1;
    move1.move[0] = 0;
    move1.move[1] = 0;
    
    test.moves.push_back(move1);
    //test.moves.move[1] = 1;
    
    MOVE pulledMove = test.moves[0];
    
    int pulledX = pulledMove.move[0];
    int pulledY = pulledMove.move[1];
    
    //test.moves.push_back(move1);
    printf("x and y coords of pulled move: %d, %d\n", pulledX,pulledY);
    
    MOVE move2;
    move2.move[0] = 2;
    move2.move[1] = 4;
    
    test.moves.push_back(move2);
    
    printf("x and y coords of pulled move: %d, %d\n", test.moves[1].move[0],test.moves[1].move[1]);
    */
    
    PIECE test;
    test.setPos(1,2);
    /*
    int x = test.getX();
    int y = test.getY();
    printf("x and y coords from pos: %d, %d\n", x,y);
     */
    int size = test.getSize();
    printf("size: %d\n", size);
    test.addMove(2,4);
    //printf("size: %d\n", test.getSize());
    test.addMove(3,3);
    test.addMove(2,2);
    int movex;
    int movey;
    for(int i = 0; i < test.getSize(); i++){
        MOVE move = test.getMove(i);
        printf("Move: %d, %d\n",move.dest[0],move.dest[1]);
    }
    PIECE test2;
    test2 = test;
    test2.clearMoves();
    printf("size: %d\n", test.getSize());
    
    
    
    
	return 0;
}

