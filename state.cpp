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

    num_empty_cells = BOARD_COLS * BOARD_ROWS;
    last_move._piece = empty;
    last_move.col = -1;
    last_move.row = -1;

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
	for(int i=0; i<BOARD_ROWS; i++)
    {
        if ( (*(s)).board[i][col] == piece::empty)
        {
            (*(s)).board[i][col] = pc;
            (*(s)).last_move.row = i;
			(*(s)).last_move.col = col;
    		(*(s)).last_move._piece = pc;
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
	for (int i = 0; i < BOARD_ROWS; i++)
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
	for (int i = 0; i < BOARD_COLS; i++)
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

bool State::insert_piece(piece pc, uint8_t col) {
	for (int i=0; i<BOARD_ROWS; i++) {
        if ( board[i][col] == piece::empty) {
            this->board[i][col] = pc;
            this->last_move.row = i;
			this->last_move.col =col;
    		this->last_move._piece = pc;
			this->num_empty_cells--;
			return true;
        }
    }
	return false;
}

bool State::remove_piece(const uint8_t row, const uint8_t col, const game_move new_last_move) {
	// returns true if piece was removed,
	// returns false if position is already empty
	if (board[row][col] == piece::empty) {
		return false;
	}
	board[row][col] = piece::empty;
	num_empty_cells++;
	last_move = new_last_move;
	return true;
}

State::~State()
{
	//todo: implement if needed, or remove
}
