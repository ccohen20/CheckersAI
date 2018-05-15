#include <iostream>
#include "Board.hpp"

MOVE search(Board board, int depth, int black){
    
    int color;
    if(black){
        color = BLACK;
    } else {
        color = WHITE;
    }
    int becomeKing = 5;
    int kill = 3;
    int center = 1;
    
    vector<PIECE> pieces;

	bestMove= 0;

    //create piece objects for pieces of the desired team
	for(int i=0; i<BOARD_LENGTH; i++){
		for(int j=0; j<BOARD_LENGTH; j++) {
			if(board[i][j]==color){
                //create new pieces
                PIECE temp;
                int pos[2] = {i,j};
                temp.pos = pos;
                temp.moves = getMoves(board, temp);
                temp.genScore();
                pieces.push_back(temp);
			}
		}
	}
    
    //find best piece to move
    int psize = pieces.size();
    int maxScore = pieces[0].maxScore;
    int maxIndex = pieces[0].maxIndex;
    int pindex = 0;
    for(int i=1; i < psize; i++){
        if(pieces[i].maxScore>maxScore){
            maxScore = pieces[i].maxScore;
            maxIndex = pieces[i].maxIndex;
            pindex = i;
        }
    }
    
    return pieces[pindex].moves[maxIndex];
    
    void getMoves(Board b, PIECE p){
        int start = p.pos;
        
        
    }
    

	//vector <board> moveList;
	vector <int> moveList;
	//implement this, babyyyyyy
	moveList = getAllMoves(moveList);



	if(moveList.size()==0) {
		bestMove = -1;
		int bestScore=-1000000;
	


	for(int i=0;i<moveList.size();i++) {
			int move=moveList[i].move;
			makeMove(moveList[i]);				
			int next=minn(depth-1);
			if(next > bestScore) {
				bestScore=next;
				bestMove=moveList[i];
			}
			unmakeMove();
		}
	} else {

		vector <MOVE> moveList;
		genallmoves(moveList);
				
		if(moveList.size() == 0)
		bestMove.move=-1;
		int bestScore=1000000;
		for(int i=0;i<moveList.size();i++) {
			int move=moveList[i].move;
			makeMove(moveList[i]);
			int next=maxx(depth-1);
			if(next < bestScore) {
				bestScore=next;
				bestMove=moveList[i];
			}
			unmakeMove();
		}
	}
	return bestMove;
}

int maxx(int depth) {

	if(depth==0)
		return evaluate();vector <MOVE> moveList;
	genallmoves(moveList);
	int bestScore=-100000;
	for(int i=0;i<moveList.size();i++)
	{
		int move=moveList[i].move;
		makeMove(moveList[i]);
		bestScore=max(bestScore,minn(depth-1));
		unmakeMove();
	}
	
	return bestScore;
}
// Min subroutine for MinMax function
int minn(int depth)
{
	if(depth==0)
		return evaluate();
	vector <MOVE> moveList;
	genallmoves(moveList);
	int bestScore=+100000;
	for(int i=0;i<moveList.size();i++)
	{
		int move=moveList[i].move;
		makeMove(move);
		bestScore=min(bestScore,maxx(depth-1));
		unmakeMove();
	}
	return bestScore;
}
