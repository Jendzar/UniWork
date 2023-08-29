#ifndef STRUCTURE_H_
#define STRUCTURE_H_
typedef struct
{
    int current_player;
    int m,n; /*dimensions of the board*/
    int number_of_penguins;
    int num_placed_penguins_player1;
    int num_placed_penguins_player2;
    int placement_coord_x,placement_coord_y;
    int penguin_position_x, penguin_position_y;
    int movement_x,movement_y;
    int score_counter_1,score_counter_2;
    int number_of_fish_on_board;
    int fishes;
}Game_phase;
#endif//STRUCTURE_H_