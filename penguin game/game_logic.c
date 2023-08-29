#include<stdio.h>
#include<windows.h>
#include <unistd.h>
#include"game_logic.h"
Game_phase game;
int is_route_clear(Game_phase game,int board[250][250]);
int position_valid(Game_phase game,int board[250][250])
{
        if(board[game.placement_coord_y][game.placement_coord_x]==1)
            return 1;
        else if(game.placement_coord_x>game.m||game.placement_coord_y>game.n||game.placement_coord_x<0||game.placement_coord_y<0)
            return 0;
        else
            return 0;

}
int are_there_any_fish_left(Game_phase game)
{
     game.fishes = 0;
    for(int i = 0; i < game.m; i++){
        for(int k = 0; k < game.n; k++){
            if(board[i][k] == 1){
                game.fishes += 1;
            }
            if(board[i][k] == 2){
                game.fishes += 1;
            }
            if(board[i][k] == 3){
                game.fishes += 1;
            }
        }
    }

    if(game.fishes == 0){
        return 0;
    }
    else{
        return 1;
    }
}
void increase_score(Game_phase *game)
{
 if (game->current_player == 1)
 {
    if(board[game->movement_y][game->movement_x] == 1)
    {
        game->score_counter_1 += 1;
    }
    else if(board[game->movement_y][game->movement_x] == 2) 
    {
        game->score_counter_1 += 2;
    }
    else if(board[game->movement_y][game->movement_x] == 3)
    {
        game->score_counter_1 += 3;
    }
 }
 if (game->current_player == 2)
 {
     if(board[game->movement_y][game->movement_x] == 1)
     {
         game->score_counter_2 += 1;
     }
     else if(board[game->movement_y][game->movement_x] == 2)
     {
         game->score_counter_2 += 2;
     }
     else if(board[game->movement_y][game->movement_x] == 3)
     {
         game->score_counter_2 +=3;
     }
 }
}
int movement_forbidden(Game_phase game,int board[250][250])
{
    if(game.current_player==1)
    {
        if(board[game.penguin_position_y][game.penguin_position_x]!=10)
        {
            system("cls");
            printf("\t\t\tWRONG PENGUIN POSITION\n");
            sleep(2);
            return 0;
        }
        else if(!(game.movement_x==game.penguin_position_x||game.movement_y==game.penguin_position_y))
        {
            system("cls");
            printf("\t\t\tYOU CAN'T MOVE DIAGONALLY\n");
            sleep(2);
            return 0;
        }
        else if(!(is_route_clear(game,board)))
        {
            system("cls");
            printf("\t\t\tMOVEMENT AGAINST RULES\n");
            sleep(2);
            return 0;
        }
    }
    else if(game.current_player==2)
    {
        if(board[game.penguin_position_y][game.penguin_position_x]!=20)
        {
            system("cls");
            printf("\t\t\tWRONG TEAM\n");
            sleep(2);
            return 0;
        }
        else if(!(game.movement_x==game.penguin_position_x||game.movement_y==game.penguin_position_y))
        {
            system("cls");
            printf("\t\t\tYOU CAN'T MOVE DIAGONALLY\n");
            sleep(2);
            return 0;
        }
        
    }
    return 1;
}
int is_route_clear(Game_phase game,int board[250][250])
{
   /*if(game.movement_y==game.penguin_position_y)
    {   
        if(game.penguin_position_y<game.movement_y)
        {
             for(int i=game.penguin_position_y;i<game.movement_y;i++)
            {
                if(board[game.penguin_position_y][i]!=1&&board[game.penguin_position_y][i]!=2&&board[game.penguin_position_y][i]!=3)
                return 0;
            }
        }
        else
        {
             for(int i=game.penguin_position_y;i>game.movement_y;i--)
            {
                if(board[game.penguin_position_y][i]!=1&&board[game.penguin_position_y][i]!=2&&board[game.penguin_position_y][i]!=3)
                return 0;
            }
        }
       
    }
    else if(game.movement_x==game.penguin_position_x)
    {
        if(game.penguin_position_x<game.movement_x)
        {
              for(int i=game.penguin_position_x;i<game.movement_x;i++)
            {
                if(board[i][game.penguin_position_x]!=1&&board[i][game.penguin_position_x]!=2&&board[i][game.penguin_position_x]!=3)
                return 0;
            }
        }
        else
        {
            for(int i=game.penguin_position_x;i>game.movement_x;i--)
            {
                if(board[i][game.penguin_position_x]!=1&&board[i][game.penguin_position_x]!=2&&board[i][game.penguin_position_x]!=3)
                return 0;
            }   
        }
    }
    return 1;*/
}