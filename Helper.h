#include <stdint,h>

struct pos {
	uint8_t x;
	uint8_t y;

	pos(uint8_t x, uint8_t y)
	{
		this->x = x;
		this->y = y;
	}
};


enum player { us = 1, them = -1, empty = 0};