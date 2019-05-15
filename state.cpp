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

	this->num_empty_cells = x.num_empty_cells;
	this->last_move = x.last_move;
    

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
	this->num_empty_cells = x.num_empty_cells - 1 ;
	this->last_move = p;
    this->board[p.row][p.col] = p._piece;
}
bool State::make_move(piece pc, uint8_t col, State* s) const//ezay ast5dem el copy constructor gwa el fn????
{
  
	bool ret = false;
    (*(s)).last_move.col =col;
    (*(s)).last_move._piece = pc;

	for(int i=0; i<BOARD_ROWS; i++)
    {
        if ( (*(s)).board[i][col] == piece::empty)
        {
            (*(s)).last_move.row = i;
            (*(s)).board[i][col] = (*(s)).last_move._piece;
			(*(s)).num_empty_cells--;
			ret=true;
			break;
        }
    }


	return ret;
}

piece State::utility() const{
	
	int count = 0;
	//TODO edge case for laspmove is empty
	piece play = last_move._piece;
	//Horizontal test 
	for (int i = 0; i < BOARD_COLS; i++)
	{
		if (play == board[i][last_move.col])
		{
			count++;
		}
		else
			count = 0;

		if (count >= 4)
			return play;
	}

	//vertical test
	count = 0;
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		if (play == board[last_move.row][i])
		{
			count++;
		}
		else
		{
			count = 0;
		}

		if (count >= 4)
			return play;
	}

	//check upper upward diagonal  
	if (last_move.row > last_move.col) {
		count = 0;
		int j = 0;
		for (int i = last_move.row - last_move.col; i < BOARD_ROWS && j < BOARD_COLS; i++) {
			if (board[i][j] == play) {
				count++;
				if (count >= 4)
					return play;
			}
			else
				count = 0;
			j++;
		}
	}

	//check lower upward diagonal
	else {
		count = 0;
		int i = 0;
		for (int j = last_move.col - last_move.row ; i < BOARD_ROWS && j < BOARD_COLS; j++) {
			if (board[i][j] == play) {
				count++;
				if (count >= 4)
					return play;
			}
			else
				count = 0;
			i++;
		}
	}

	//check left downward diagonal     
	if (last_move.col + last_move.row < 6) {
		count = 0;
		int i = 0;
		for (int j = last_move.col + last_move.row; j >= 0 && i < BOARD_ROWS; j--) {
			if (board[i][j] == play) {
				count++;
				if (count >= 4 )
					return play;
			}
			else
				count = 0;
			i++;
		}
	}

	//check right downward diagonal
	else {
		count = 0;
		int j = last_move.row - (5 - last_move.col);
		for (int i = 5; i >= (last_move.row + last_move.col) - 6; i--) {
			if (board[i][j] == play) {
				count++;
				if (count >= 4)
					return play;
			}
			else
				count = 0;
			j++;
		}
	}
	return piece::empty;
}

State::~State()
{
	//todo: implement if needed, or remove
}
