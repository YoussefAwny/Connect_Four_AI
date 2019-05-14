#include <stdint>

struct pos {
	uint8_t x;
	uint8_t y;
};


enum player { us = 1, them = -1, empty = 0};