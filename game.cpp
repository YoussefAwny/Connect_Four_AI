#include "game.h"

Game::Game(Player *p1, Player *p2)
{
    this->player1 = p1;
    this->player2 = p2;
}

Game::~Game()
{
    delete player1;
    delete player2;
}

void Game::init()
{
    turn = player1;
    finished = false;
    for ( int i = 0; i<7 ; i++ )
    {
        for (int j=0; j<6; j++)
        {
            grid[i][j]='0';
        }
    }
}

void Game::switchTurn()
{
    if(turn==player1)
        turn = player2;
    else
        turn = player1;
}

bool Game::winCheck(int x, int y)
{
    int count =0;
    char color = grid[x][y];
    // Horizontal check
    for ( int i =0; i<7 ; i++)
    {
        if( color == grid[i][y])
        {
            count++;
        }

        if (count >=4)
            return true;
    }

    //vertical check

    count =0;
    for ( int i =0; i<6 ; i++)
    {
        if( color == grid[x][i])
        {
            count++;
        }

        if (count >=4)
            return true;
    }

    //check lower upward diagonal   (WORKING)
    if(x > y) {
        count = 0;
        int j = 0;
        for(int i = x - y; i < 7; i++) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            j++;
        }
    }

    //check upper upward diagonal
    else {
        count = 0;
        int i = 0;
        for(int j = y - x; j < 6; j++) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            i++;
        }
    }

    //check lower downward diagonal     (WORKING)
    if(x+y < 6) {
        count = 0;
        int i = 0;
        for(int j = x+y; j >= 0; j--) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            i++;
        }
    }

    //check upper downward diagonal     (WORKING)
    else {
        count = 0;
        int i = x - (5-y);
        for(int j = 5; j >= (x+y) - 6; j--) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            i++;
        }
    }
    return false;
}

 int Game::play(int x)
{
     int y;

     for(int i=0;i<6;i++){
         if(grid[x][i] == '0') {
             y = i;
             break;
         }
     }

     grid[x][y] = turn->getcolor();
     if(winCheck(x,y)) {
         turn->setscore(turn->getscore() + 1);
         finished = true;
     }
     else
         switchTurn();
     return y;
 }


