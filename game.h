#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>
#include "Player.h"

class Game
{
private:
    Player *player1, *player2, *turn;
    char grid[7][6];
    bool finished;
    bool winCheck(int x, int y);
    void switchTurn();

public:
    Game(Player *p1, Player *p2);
    ~Game();

    void init();
    int play(int x);

    void setPlayer1(Player *p){
        player1 = p;
    }

    void setPlayer2(Player *p){
        player2 = p;
    }

    Player* getPlayer1(){
        return player1;
    }

    Player* getPlayer2(){
        return player2;
    }

    Player* turnToPlay(){
        return turn;
    }

    char getgrid(int x, int y)
    {
        return grid[x][y];
    }

     bool isFinished() const {
         return finished;
     }


};

#endif // GAME_H
