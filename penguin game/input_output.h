#ifndef INPUT_OUTPUT_H_
#define INPUT_OUTPUT_H_
#include"structure.h"
extern int board[250][250];
void ask_for_dimensions_and_penguin_numb(Game_phase *game);
void ask_for_placement(Game_phase *game);
void get_movement(Game_phase *game);
void show_score(Game_phase game);
void show_players_and_score(Game_phase game);


#endif //INPUT_OUTPUT_H_