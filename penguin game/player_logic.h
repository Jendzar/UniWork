#ifndef PLAYER_LOGIC_H_
#define PLAYER_LOGIC_H_
#include "structure.h"
extern int board[250][250];
void set_player_to_1(Game_phase *game);
int penguins_left_of_any_player(Game_phase game);
int penguins_left_of_current_player(Game_phase game);
void change_player(Game_phase *game);
int are_there_any_possible_movements_for_any_player(Game_phase game,int board[250][250]);
int are_there_any_posible_movement_for_current_player(Game_phase game,int board[250][250]);



#endif //PLAYER_LOGIC_H_