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
bool State::make_move(piece pc, uint8_t col, State* s) const//ezay ast5dem el copy constructor gwa el fn????
{
  
	bool ret = false;
    (*(s)).last_move.col =col-1;
    (*(s)).last_move._piece = pc;

    for(int i=BOARD_ROWS-1; i>=0; i--)
    {
        if ( (*(s)).board[i][col-1] == piece::empty)
        {
            (*(s)).last_move.row = i;
            (*(s)).board[i][col-1] = (*(s)).last_move._piece;
			(*(s)).num_empty_cells--;
			ret=true;
			break;
        }
    }


	return ret;
}

piece State::utility() const{
    //todo: implement

	/*for testing*/
	piece won=empty;
	return won;
	/*for testing*/
}

State::~State()
{
	//todo: implement if needed, or remove
}
