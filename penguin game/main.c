
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include"board.h"
#include"input_output.h"
#include"game_logic.h"
#include"player_logic.h"
    int board[250][250];

int main()
{

    srand(time(NULL));
   Game_phase game;
   game.num_placed_penguins_player1=0;
   game.num_placed_penguins_player2=0;
   game.score_counter_1=0;
   game.score_counter_2=0;
      /**placement phase**/
   ask_for_dimensions_and_penguin_numb(&game);
   generate_board(board,game.m,game.n,game.number_of_penguins);
   set_player_to_1(&game);

   while(penguins_left_of_any_player(game))
    {

      if(penguins_left_of_current_player(game))
       {
           do
           {
               show_board(game.m,game.n,game.current_player);
               ask_for_placement(&game);
           }while(!position_valid(game,board));

           place_penguin(&game,board);
           change_player(&game);
       }
       else
       {
            change_player(&game);
       }

   }
   show_board(game.m,game.n,game.current_player);
            /** movement phase**/
  set_player_to_1(&game);
  
    while(are_there_any_fish_left(game))
    {
        if(are_there_any_possible_movements_for_any_player(game,board))
        {
            if(are_there_any_posible_movement_for_current_player(game,board))
            {

                do
                {
                    show_board(game.m,game.n,game.current_player);
                    show_score(game);
                    get_movement(&game);
                }while(!movement_forbidden(game,board));
            }
            else
            {
                change_player(&game);
                do
                    {
                        show_board(game.m,game.n,game.current_player);
                        show_score(game);
                        get_movement(&game);
                    }while(!movement_forbidden(game,board));

            }
            increase_score(&game);
            remove_fish(game,board);
            move_penguin(game,board);
            remove_ice_floe(game,board);
            change_player(&game);
            show_board(game.m,game.n,game.current_player);
        }
        else
            break;
    }
    show_players_and_score(game);
}
