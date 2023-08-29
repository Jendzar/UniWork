#ifndef BOARD_H_
#define BOARD_H_ 
#include"structure.h"
extern int board[250][250];
void generate_board(int board[250][250],int m,int n,int fish);
void show_board(int m,int n,int current_player);
void place_penguin(Game_phase *game,int board[250][250]);
void remove_fish(Game_phase game,int board[250][250]);
void move_penguin(Game_phase game,int board[250][250]);
void remove_ice_floe(Game_phase game,int board[250][250]);


#endif //BOARD_H_