#include "state.h"

State::State()
{
	
	
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

	for (int i = 0 ; i< BOARD_ROWS ;i++)
	{
		for (int j = 0 ; j<BOARD_COLS ; j++)
		{
			this->board[i][j] = x.board[i][j];
		}
	}
    

}

State::State(const State &x, game_move &p)
{
    for (int i = 0 ; i< BOARD_ROWS ;i++)
	{
		for (int j = 0 ; j<BOARD_COLS ; j++)
		{
			this->board[i][j] = x.board[i][j];
		}
	}
    this->board[p.row][p.col] = p._piece;
}
State State::make_move(piece &pc, uint8_t col)//ezay ast5dem el copy constructor gwa el fn????
{
	State result= *(this);
    result.last_move.col =col-1;
    result.last_move._piece = pc;

    for(int i=BOARD_ROWS-1; i>=0; i--)
    {
        if ( result.board[i][col-1] == piece::empty)
        {
            result.last_move.row = i;
            result.board[i][col-1] = result.last_move._piece;
			break;
        }
    }

	
	return result;
}


State :: ~State()
{
	
}
