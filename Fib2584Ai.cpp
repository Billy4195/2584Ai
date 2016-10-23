#include "Fib2584Ai.h"
#include <iostream>
#include <cstdio>

using namespace std;

const int fibonacci_[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	  srand(time(NULL));
    get_weight_table(); 
	  return;
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	  MoveDirection randomMove = static_cast<MoveDirection>(rand() % 4);
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
