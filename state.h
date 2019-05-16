#include "helper.h"

#ifndef STATE_H
#define STATE_H

#define BOARD_ROWS 6
#define BOARD_COLS 7


class State
{
private:
    uint8_t num_empty_cells;

public:
    piece board[BOARD_ROWS] [BOARD_COLS];
    game_move last_move; //todo: change to getter method?
    State();
    State(const State &x);
    State(const State &x, game_move &p);
    ~State();
    piece utility() const;
    bool make_move(const piece pc, uint8_t col, State* s) const;
    bool insert_piece(const piece pc, uint8_t col);
    bool remove_piece(const uint8_t row, const uint8_t col, const game_move new_last_move);
    bool is_full() const
    {
        return num_empty_cells==0;
    }
};

#endif // STATE_H
