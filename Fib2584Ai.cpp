#include "Fib2584Ai.h"
#include <iostream>
#include <cstdio>

using namespace std;

const int fibonacci_[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

#define F_MAX 22
#define TABLE_SIZE 8*F_MAX*F_MAX*F_MAX*F_MAX

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
void Fib2584Ai::get_weight_table(){
    FILE *fp;
    int read_count;
    fp = fopen("weight_table.dat","rb");
    table.resize(TABLE_SIZE,0.0);
    if(!fp){
        cout<<"weight_table.dat open failed"<<endl;
    }else{
        for(int i=0;i<TABLE_SIZE;i++){
            read_count = fread((void*)&table[i],sizeof(weight),1,fp);
            if(!read_count){
                cout<<"weight table read failed"<<endl;
            }
        }
    }
}

void Fib2584Ai::flush_weight_table(){
    FILE *fp;
    unsigned long write_count;
    fp = fopen("weight_table.dat","wb");
    if(!fp){
        cout <<"weight_table.dat create failed"<<endl;
    }
    for(int i=0;i<TABLE_SIZE;i++){
        write_count = fwrite((void*)&table[i],sizeof(weight),1,fp);
        if(!write_count){
            cout<<"WRITE weight table failed"<<endl;
            break;
        }
    }
    fclose(fp);
}
