#include "Helper.h"

#ifndef STATE_H
#define STATE_H

#define BOARD_ROWS 6
#define BOARD_COLS 7


class State
{
private:
    piece board[BOARD_ROWS][BOARD_COLS];
    game_move last_move;
    uint8_t num_empty_cells;

public:
    State();
    State(const State &x);
    State::State(const State &x, game_move &p);
    ~State();
    piece utility();
    State* make_move(piece &pc, uint8_t col);
    bool isfull()
    {
        return num_empty_cells==0;
    }

};

#endif // STATE_H
