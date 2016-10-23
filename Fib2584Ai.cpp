#include "Fib2584Ai.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int fibonacci_[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

#define F_MAX 22
#define TABLE_SIZE 8*F_MAX*F_MAX*F_MAX*F_MAX
#define MAX(a,b) (((a)>(b))?(a):(b))

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
    transform_board(board);
	  MoveDirection randomMove = select_move(board);
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
void Fib2584Ai::transform_board(int board[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int t=0;t<32;t++){
                if(board[i][j] == fibonacci_[t]){
                    board[i][j] = t;
                }
            }
        }
    }
}
MoveDirection Fib2584Ai::select_move(int board[4][4]){
    int board_[4][4][4];
    int reward[4];
    MoveDirection next_move;
    for(int i=0;i<4;i++){
        compute_next_board(board,board_[i],reward[i],static_cast<MoveDirection>(i));
    }
    next_move = select_maxV_move_and_record(board, board_, reward);
    return next_move;
}
void Fib2584Ai::compute_next_board(int board[4][4],int board_[4][4],int &reward,MoveDirection move){
    memcpy(board_,board,sizeof(int)*4*4);
    switch(move){
        case MOVE_UP:
        case MOVE_DOWN:
            reward = move_col(board_,move);
            break;
        case MOVE_RIGHT:
        case MOVE_LEFT:
            reward = move_row(board_,move); 
            break;
    }
}
MoveDirection Fib2584Ai::select_maxV_move_and_record(int board[4][4],int board_[4][4][4], int reward[4]){
    double value[4];
    double V_max;
    vector<int> max_list;
    MoveDirection move;
    int move_t;
    record rec;
    for(int i=0;i<4;i++){
        value[i] = Evaluate(board_[i]) + reward[i]; 
    }
    V_max = value[0];
    max_list.push_back(0);
    for(int i=1;i<4;i++){
        if(value[i] > V_max){
            V_max = value[i];
            max_list.clear();
            max_list.push_back(i);
        }else if(value[i] == V_max){
            max_list.push_back(i);
        }
    }
    move_t = max_list[rand() % max_list.size()];
    move = static_cast<MoveDirection>(move_t);
    memcpy((void*)rec.board,board,sizeof(int)*4*4);
    memcpy((void*)rec.board_,board_[move_t],sizeof(int)*4*4);
    rec.reward = reward[move_t];
    Records.push(rec);
   
    return move;

}
int Fib2584Ai::move_col(int board_[4][4],MoveDirection move){
    int reward=0;
    int start_row = move == MOVE_UP ? 0 : 3;
    int end_row = move == MOVE_UP ? 3 : 0;
    int it = move == MOVE_UP ? 1 : -1;
    for(int i=0;i<4;i++){
        for(int j=start_row; j != end_row ; j += it){
            if((board_[j][i] == board_[j+it][i] && board_[j][i] == 1) ||
                (board_[j][i] >= 1 && board_[j+it][i] >= 1 &&abs(board_[j][i] 
                - board_[j+it][i]) == 1) ){
                board_[j][i] = MAX(board_[j][i],board_[j+it][i]) + 1;
                reward += fibonacci_[ board_[j][i] ];
                for(int k=j+it; k!= end_row; k += it){
                    board_[k][i] = board_[k+it][i];
                }
                board_[end_row][i] = 0;
            }
        }
    }
    return reward;
}
int Fib2584Ai::move_row(int board_[4][4],MoveDirection move){
    int reward=0;
    int start_col = move == MOVE_LEFT ? 0 : 3;
    int end_col = move == MOVE_LEFT ? 3 : 0;
    int it = move == MOVE_LEFT ? 1 : -1;
    for(int i=0;i<4;i++){
        for(int j=start_col; j != end_col ; j += it){
            if((board_[i][j] == board_[i][j+it] && board_[i][j] == 1) ||
                (board_[i][j] >= 1 && board_[i][j+it] >= 1 &&abs(board_[i][j] 
                - board_[i][j+it]) == 1) ){
                board_[i][j] = MAX(board_[i][j],board_[i][j+it]) + 1;
                reward += fibonacci_[ board_[i][j] ];
                for(int k=j+it; k!= end_col; k += it){
                    board_[i][k] = board_[i][k+it];
                }
                board_[i][end_col] = 0;
            }
        }
    }
    return reward;
}
double Fib2584Ai::Evaluate(int board[4][4]){
    unsigned long index[8],ind;
    double value=0.0;
    get_index(board,index);
    for(int i=0;i<8;i++){
        value += table[index[i]];
    }
    return value;
}
void Fib2584Ai::get_index(int board[4][4],unsigned long index[8]){
    unsigned long tmp=0;
    for(int i=0;i<4;i++){ 
        tmp += i * F_MAX * F_MAX * F_MAX * F_MAX;
        tmp += board[i][0] * F_MAX * F_MAX * F_MAX;
        tmp += board[i][1] * F_MAX * F_MAX;
        tmp += board[i][2] * F_MAX;
        tmp += board[i][3];
        index[i] = tmp;
        tmp = 0;
    }
    for(int i=0;i<4;i++){
        tmp += (4+i) * F_MAX * F_MAX * F_MAX * F_MAX;
        tmp += board[0][i] * F_MAX * F_MAX * F_MAX;
        tmp += board[1][i] * F_MAX * F_MAX;
        tmp += board[2][i] * F_MAX;
        tmp += board[3][i];
        index[4+i] = tmp;
        tmp = 0;
    }
}
