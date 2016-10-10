#include "Fib2584Ai.h"
#include <stdio.h>

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	return;
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
  static int record[4][4]={};
  static int last_two_move=-1,last_one_move=-1;
  bool changed=0;
  MoveDirection randomMove;
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(board[i][j] != record[i][j]){
        changed = 1;
        break;
      }
    }
  }
  if(!changed){
    if( (last_one_move == 0 && last_two_move == 1) || (last_one_move == 1 && last_two_move == 0) ){
      randomMove = static_cast<MoveDirection>(rand() % 2 + 2);
    }else if(last_one_move > 2){
      if(last_one_move == 2)
        randomMove = static_cast<MoveDirection>(3);
      else
        randomMove = static_cast<MoveDirection>(2);
    }else{
      randomMove = static_cast<MoveDirection>(last_one_move ^ 1 );  
    }
  }else{
    if(last_one_move == 2)
      randomMove = static_cast<MoveDirection>(0);
    else if(last_one_move == 3)
      randomMove = static_cast<MoveDirection>(1);
    else
	    randomMove = static_cast<MoveDirection>(rand() % 2);
  }
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      record[i][j] = board[i][j];
    }
  }
  last_two_move = last_one_move;
  last_one_move = static_cast<int>(randomMove);
	return randomMove;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
