#include <iostream>

search(int depth){

	bestMove= 0;
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
