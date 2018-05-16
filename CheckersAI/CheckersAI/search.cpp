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
            return scoreBoard(b,computer);
        } 
        else {
            vector<Move> moves = getMoves(b,computer);
            int size = moves.size();
            int bestVal = BIGNEG;
            for(int i = 0; i < size; i++){
                Move move = moves[i];
                Board temp = b.copyBoard();

                temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);

                vector<Move> jumps = getJumps(temp, move.newX, move.newY);
                int isJump = abs(move.newX - move.oldX) - 1;
                //handles jumping case
                if ((int)jumps.size() != 0 && isJump == 1) {

                    for (int j = 0; j < (int)jumps.size(); j++) {
                        Move jump = jumps[j];
                        Board newTemp = temp.copyBoard();
                        newTemp.movePiece(jump.oldX, jump.oldY, jump.newX, jump.newY);

                        //min
                        int moveVal = minmax(newTemp, depth-1, player);
                        //maximizing worst outcomes
                        if(moveVal > bestVal){
                            bestVal = moveVal;
                        }
                    }
                }
                //case where board can not jump anymore
                else {
                    //min
                    int moveVal = minmax(temp, depth-1, player);
                    //maximizing worst outcomes
                    if(moveVal > bestVal){
                        bestVal = moveVal;
                    }
                }
            }
            return bestVal;
        }
    }
    //best player move 
    else {
        //basecase
        if(depth==0){
            return scoreBoard(b,computer);
        } 
        else {
            vector<Move> moves = getMoves(b,player);
            int size = moves.size();
            int bestVal = BIGPOS;
            for(int i = 0; i < size; i++){
                Move move = moves[i];
                Board temp = b.copyBoard();

                temp.movePiece(move.oldX,move.oldY,move.newX,move.newY);

                vector<Move> jumps = getJumps(temp, move.newX, move.newY);
                //handles jumping case
                int isJump = abs(move.newX - move.oldX) - 1;
                if ((int)jumps.size() != 0 && isJump == 1) {

                    for (int j = 0; j < (int)jumps.size(); j++) {
                        Move jump = jumps[j];
                        Board newTemp = temp.copyBoard();
                        newTemp.movePiece(jump.oldX, jump.oldY, jump.newX, jump.newY);

                        //min
                        int moveVal = minmax(newTemp, depth-1, computer);
                        //maximizing worst outcomes
                        if(moveVal < bestVal){
                            bestVal = moveVal;
                        }
                    }
                }
                else {
                    //min
                    int moveVal = minmax(temp, depth-1, computer);
                    //minimizing best outcomes
                    if(moveVal < bestVal){
                        bestVal = moveVal;
                    }
                }
            }
            return bestVal;
        }
    }
}


Move searchJump(Board b, int depth, int x, int y) {
    
    Move bestMove;
    int bestVal;

    vector<Move> moves;
    moves = getJumps(b, x, y);
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

    





