#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString name;
    char color;
    int score;


public:
    Player();
    Player(QString _name, char _color);
    void setname(QString _name);
    QString getname();
    void setscore( int _score);
    int getscore();
    void setcolor(char _color);
    char getcolor();


};

#endif // PLAYER_H
