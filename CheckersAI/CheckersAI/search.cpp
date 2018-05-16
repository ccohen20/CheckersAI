#include <iostream>
#include "Board.hpp"
#include "AI.hpp"


int BIGNEG = -100000;
int BIGPOS = 100000;

int minmax(Board b, int depth, int bot){
    //best bot move
    if(bot){
        //basecase
        if(depth==0){
            return scoreBoard(b,1);
        } 
        else {
            vector<Move> moves = getMoves(b,1);
            int size = moves.size();
            int bestVal = BIGNEG;
            for(int i = 0; i < size; i++){
                Move move = moves[i];
                Board temp = b.copyBoard();

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
            vector<Move> moves = getMoves(b,0);
            int size = moves.size();
            int bestVal = BIGPOS;
            for(int i = 0; i < size; i++){
                Move move = moves[i];
                Board temp = b.copyBoard();

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


Move search(Board b, int depth, int bot){

    Move bestMove;
    int bestVal;


    if(bot){
        vector<Move> moves;
        moves = getMoves(b,bot);
        int size = moves.size();

        bestVal = BIGNEG;
        for(int i = 0; i < size; i++){
            Move move = moves[i];
            Board temp = b.copyBoard();


            temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);
            //min
            int moveVal = minmax(temp, depth-1, 0);
            //maximizing worst outcomes
            if(moveVal > bestVal){
                bestVal = moveVal;
                bestMove = move;
            }
        }
        return bestMove;
    } else {
        //player
        vector<Move> moves;
        moves = getMoves(b,0);
        int size = moves.size();


        bestVal = BIGPOS;
        for(int i = 0; i < size; i++){
            Move move = moves[i];
            Board temp = b.copyBoard();

            temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);
            //max
            int moveVal = minmax(temp, depth-1, 1);
            //minimizing best outcomes
            if(moveVal < bestVal){
                bestVal = moveVal;
                bestMove = move;
            }
        }
        return bestMove;
    }
}

    





