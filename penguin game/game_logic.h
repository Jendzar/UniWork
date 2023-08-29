#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_
#include"structure.h"
extern int board[250][250];
int position_valid(Game_phase game,int board[250][250]);
/* 
* This function checks if placement of the penguin is valid
* if input is in dimensions of the board returns 1
* if penguin is placed on tile with 1 fish returns 1
* if there are previously placed penguins on tile returns 0
*/
int are_there_any_fish_left(Game_phase game);
/*
* This function checks if there are any fishes left on the board
* It counts how many fishes left are on the board
* And when counter is at 0 it returns 0
*/
void increase_score(Game_phase *game);
/*
* This function adds score to players score counter
* Checks ammount of fishes where penguin is moved
* Then adds score to score counter of player that moved
*/
int movement_forbidden(Game_phase game,int board[250][250]);
/*
* This function checks correctness of the movement
* Checks if the move is diagnall
* Checks if coordinets of penguin inputted by user is correct
* Checks if move isn't over any penguin
* Checks if move doesn't end on empty tile or tile with other penguin
*/

#endif