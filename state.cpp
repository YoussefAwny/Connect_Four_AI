#include "state.h"

State::State()
{
	
	board = new piece*[BOARD_ROWS];
	for(int i = 0; i < BOARD_ROWS; ++i)
		board[i] = new piece[BOARD_COLS];
		
	
    for ( int i=0; i< BOARD_ROWS ; i++)
    {
        for ( int j=0; j< BOARD_COLS; j++)
        {
            board[i][j] = piece::empty;
        }
    }

}

State::State(const State& x)
{
    this->board = x.board;

}

State::State(const State &x, game_move &p)
{
    this->board = x.board;
    this->board[p.row][p.col] = p._piece;
}
State* State::make_move(piece &pc, uint8_t col)//ezay ast5dem el copy constructor gwa el fn????
{
	State *s;
    last_move.col =col;
    last_move._piece = pc;

    for(int i=0; i<BOARD_ROWS; i++)
    {
        if ( board[i][col] == piece::empty)
        {
            last_move.row = i;
            board[i][col] = last_move._piece;
        }
    }

	return s;
}


State :: ~State()
{
	for(int i = 0; i < BOARD_ROWS; ++i) {
			delete[] board[i];   
		}
		
		delete[] board;
}
