#include <cstdint>

struct pos {
	uint8_t x;
	uint8_t y;

	pos(uint8_t x, uint8_t y)
	{
		this->x = x;
		this->y = y;
	}
};

struct game_move {
    uint8_t col;
    uint8_t row;
    piece _piece;
};


typedef enum piece { us = 1, them = -1, empty = 0}piece ;
