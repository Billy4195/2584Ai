#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"
#include <stack>
#include <vector>

using namespace std;

typedef struct{
    int board[4][4];
    int board_[4][4];
    int reward;
}record;

typedef double weight;

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);

	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
  void get_weight_table();
  void flush_weight_table();
  void transform_board(int board[4][4]);
  MoveDirection select_move(int board[4][4]);
  void compute_next_board(int board[4][4],int board_[4][4],int &reward,MoveDirection move);
  MoveDirection select_maxV_move_and_record(int board[4][4],int board_[4][4][4], int reward[4]);
  int move_col(int board_[4][4],MoveDirection move);
  int move_row(int board_[4][4],MoveDirection move);

  stack<record> Records;
  vector<weight> table;
};


#endif
