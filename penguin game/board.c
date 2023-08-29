#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include<windows.h>
#include"board.h"
#define ONE_FISH 1
#define TWO_FISH 2
#define THREE_FISH 3
#define PLAYER_ONE 10
#define PLAYER_TWO 20
#define ICE_FLOE 11
#define WATER 0
Game_phase game;
void change_colour(int board[250][250],int x,int y);
void generate_board(int board[250][250],int m,int n,int fish)
{
    int num_of_1fish;
    int num_1fish_placed=0;
    num_of_1fish=2*fish+2;
    int random_fish;
    int num_fish1_placed=0;
    int rand_m,rand_n;
      for(int i=0;i<num_of_1fish;i++)
        {
            rand_m=rand()%m;
            rand_n=rand()%n;
            while(board[rand_m][rand_n]==ONE_FISH)
            {
                rand_m=rand()%m;
                rand_n=rand()%n;
            }
            board[rand_m][rand_n]=ONE_FISH;
        }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            random_fish=rand()%2;
            if(board[i][j]!=ONE_FISH)
            {
                if(random_fish==0)
                board[i][j]=TWO_FISH;
                else if(random_fish==1)
                board[i][j]=THREE_FISH;
            }
        }
    }
}
void show_board(int m,int n,int current_player)
{
    system("cls");
    printf(" Turn of player: %d\n",current_player);
    printf("   ");
    for(int i=0;i<n;i++)   
    {
        printf("%4d",i);
    }printf("\n  ");       //printing barriers and coordinates
    for(int i=0;i<n;i++)
    {
        printf("____");   //printing barriers and coordinates
    }printf("\n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(j==0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN|0);
                printf("%2d | ",i);
            }
            change_colour(board,i,j);
            printf("%3d ",board[i][j]);
        }printf("\n");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN|0);
}
void place_penguin(Game_phase *game,int board[250][250])
{
    if (game->current_player==1)
       {
           game->num_placed_penguins_player1++;
           board[game->placement_coord_y][game->placement_coord_x]=10;
       }
    else
        {
            game->num_placed_penguins_player2++;
            board[game->placement_coord_y][game->placement_coord_x]=20;
        }
}

void remove_fish(Game_phase game,int board[250][250])
{
    board[game.movement_y][game.movement_x]=WATER;
}
void move_penguin(Game_phase game,int board[250][250])
{
    if(game.current_player==1)
    {
        board[game.movement_y][game.movement_x]=PLAYER_ONE;
    }
    else if(game.current_player==2)
    {
        board[game.movement_y][game.movement_x]=PLAYER_TWO;
    }
}
void remove_ice_floe(Game_phase game,int board[250][250])
{
    board[game.penguin_position_y][game.penguin_position_x]=WATER;
}
void change_colour(int board[250][250],int x,int y)
{
    if(board[x][y]==ONE_FISH||board[x][y]==TWO_FISH||board[x][y]==THREE_FISH)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15|BACKGROUND_INTENSITY);
    else if(board[x][y]==PLAYER_ONE)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0|BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
    else if(board[x][y]==PLAYER_TWO)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED | BACKGROUND_GREEN);
    else if(board[x][y]==WATER)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}