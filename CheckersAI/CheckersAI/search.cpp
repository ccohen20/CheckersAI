#include <iostream>
#include "Board.hpp"

Move search(Board board, int depth, int bot){

    int BIGNEG = -100000;
    int BIGPOS = 100000;
    
    int becomeKing = 5;
    int kill = 3;
    int center = 1;
    
    vector<Move> moves;
    moves = getMoves(board,bot);

    Move bestMove;
    int bestVal;

    int size = moves.size();

    if(bot){
        bestVal = BIGNEG;
        for(int i = 0; i < size; i++){
            Move move = moves[i];
            Board temp = board.copy();


            temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);
            //min
            int moveVal = minmax(temp, depth-1, 0);
            //maximizing worst outcomes
            if(moveVal > bestVal){
                bestVal = moveVal;
                bestMove = move;
            }
        }
    } else {
        //player
        bestVal = BIGPOS;
        for(int i = 0; i < size; i++){
            Move move = moves[i];
            Board temp = board.copy();

            temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);
            //max
            int moveVal = minmax(temp, depth-1, 1);
            //minimizing best outcomes
            if(moveVal < bestVal){
                bestVal = moveVal;
                bestMove = move;
            }
        }

    }
    }

int minmax(Board b, int depth, int bot){
    //best bot move
    if(bot){
        //basecase
        if(depth==0){
            return scoreBoard(b,1);
        } 
        else {
            vector<Move> moves = b.getMoves(b,0);
            int size = moves.size();
            int bestVal = BIGNEG;
            for(int i = 0; i < size; i++){
                Move move = moves[i];
                Board temp = board.copy();

                temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);
                //min
                int moveVal = minmax(temp, depth-1, 0);
                //maximizing worst outcomes
                if(moveVal > bestVal){
                    bestVal = moveVal;
                }
            }
            return bestVal;
        }
    }
    //best player move 
    else {
        //basecase
        if(depth==0){
            return scoreBoard(b,1);
        } 
        else {
            vector<Move> moves = b.getMoves(b,1);
            int size = moves.size();
            int bestVal = BIGPOS;
            for(int i = 0; i < size; i++){
                Move move = moves[i];
                Board temp = board.copy();

                temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);
                //min
                int moveVal = minmax(temp, depth-1, 1);
                //minimizing best outcomes
                if(moveVal < bestVal){
                    bestVal = moveVal;
                }
            }
            return bestVal;
        }
    }
}

    





