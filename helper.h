#ifndef HELPER_H
#define HELPER_H

#include <cstdint>

//todo: remove struct pos (unused)
struct pos {
	uint8_t x;
	uint8_t y;

	pos(uint8_t x, uint8_t y)
	{
		this->x = x;
		this->y = y;
	}
};

enum piece { us = 1, them = -1, empty = 0} ;

struct game_move {
    uint8_t col;
    uint8_t row;
    piece _piece;
};

#endif //HELPER_H
