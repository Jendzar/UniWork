#include<stdio.h>
#include"input_output.h"
Game_phase game;
void ask_for_dimensions_and_penguin_numb(Game_phase *game)
{
    int m,n,peng_num;
   do
   {
        printf("Enter dimensions of the board: ");
        scanf("%d %d",&m,&n);
        printf("Enter number of penguins: ");
        scanf("%d",&peng_num);
   } while (m<=1||n<=1||peng_num<=0);
    game->m=m;
    game->n=n;
    game->number_of_penguins=peng_num;
}
void ask_for_placement(Game_phase *game)
{
    printf("Give coordinates of placement: \n");
    scanf("%d%d",&game->placement_coord_x,&game->placement_coord_y);
}
void get_movement(Game_phase *game)
{
    printf("Give coordinates of penguin you want to move: ");
    scanf("%d%d",&game->penguin_position_x,&game->penguin_position_y);
    printf("Give coordinates of movement: ");
    scanf("%d%d",&game->movement_x,&game->movement_y);
}
void show_score(Game_phase game)
{
    printf("Score of player one: %d\n",game.score_counter_1);
    printf("Score of player two: %d\n",game.score_counter_2);
}
void show_players_and_score(Game_phase game)
{
    printf("Player 1: %d\n", game.score_counter_1);
    printf("Player 2: %d\n\n", game.score_counter_2);
    if(game.score_counter_1 > game.score_counter_2)
    {
      printf("\t\t\tThe winner is Player 1!\n");
    }
    else if(game.score_counter_1 < game.score_counter_2)
    {
      printf("\t\t\tThe winner is Player 2!\n");
    }
    else
    {
      printf("\t\t\tThe game is a draw!\n");
    }
}
