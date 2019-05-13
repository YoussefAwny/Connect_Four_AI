#include "player.h"
Player::Player(){}
Player::Player(QString _name, char _colour) {
    name = _name;
    color = _colour;
    score = 0;
}


void Player::setcolor(char _color)
{
    this->color = _color;
}

void Player::setname(QString _name)
{
    this->name = _name;
}

void Player::setscore(int _score)
{
    this->score = _score;
}

char Player::getcolor()
{
    return this->color;
}

QString Player::getname()
{
    return this->name;
}

int Player::getscore()
{
    return this->score;
}
