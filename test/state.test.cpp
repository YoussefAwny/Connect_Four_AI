#include "state.test.h"
#include <iostream>
#include <vector>
using namespace std;

//Function to print the board
void print_board (State s)
{
	for (int i = BOARD_ROWS -1 ; i>=0 ; i--)
		{
			for (int j=0 ; j<BOARD_COLS ; j++ )
			{
				if (s.last_move.row == i && s.last_move.col == j) {
                    if(s.board[i][j]==-1)
                        cout<<"X";
                    else if(s.board[i][j]==1)
                        cout<<"X";
                    else
                        cout << "_";
                } else {
                    if(s.board[i][j]==-1)
                        cout<<"2";
                    else if(s.board[i][j]==1)
                        cout<<s.board[i][j];
                    else
                        cout << "_";
                }
				cout<<" ";
			}
			cout<<endl;
		}
	cout<<endl<<endl;
}


vector<State> generate_win_rows(int last_move) {
    vector<State> vec;
    vec.reserve(50);
    //rows
    for(int row=0; row<BOARD_ROWS; ++row) {
        for(int col=0; col<BOARD_COLS-num+1; ++col) {
            State s;
            for (int i=col; i<col+num; ++i) {
                s.board[row][i] = fill_piece;
            }
            s.last_move.col = col+last_move-1;
            s.last_move.row = row;
            s.last_move._piece = fill_piece;
            vec.push_back(s);
        }
    }
    return vec;
}

vector<State> generate_win_cols(int last_move) {
    vector<State> vec;
    vec.reserve(50);
    //cols
    for(int col=0; col<BOARD_COLS; ++col) {
        for (int row=0; row<BOARD_ROWS-num+1; ++row) {
            State s;
            for (int i=row; i<row+num; ++i) {
                s.board[i][col] = fill_piece;
            }
            s.last_move.row = row+last_move-1;
            s.last_move.col = col;
            s.last_move._piece = fill_piece;
            vec.push_back(s);
        }
    }
    return vec;
}

std::vector<State> generate_win_45(int last_move) {
    vector<State> vec;
    vec.reserve(50);
    //45 degree diagonals
    for (int col=0; col<BOARD_COLS-num+1; ++col) {
        for (int row=0; row<BOARD_ROWS-num+1; ++row) {
            State s;
            for (int i=0; i<num; ++i) {
                s.board[row+i][col+i] = fill_piece;
            }
            s.last_move.row = row+last_move-1;
            s.last_move.col = col+last_move-1;
            s.last_move._piece = fill_piece;
            vec.push_back(s);
        }
    }
    return vec;
}

std::vector<State> generate_win_135(int last_move) {
    vector<State> vec;
    vec.reserve(50);
    //135 degree diagonals
    for (int col=BOARD_COLS-num; col<BOARD_COLS; ++col) {
        for (int row=0; row<BOARD_ROWS-num+1; ++row) {
            State s;
            for (int i=0; i<num; ++i) {
                s.board[row+i][col-i] = fill_piece;
            }
            s.last_move.row = row+last_move-1;
            s.last_move.col = col-(last_move-1);
            s.last_move._piece = fill_piece;
            vec.push_back(s);
        }
    }
    return vec;
}

void generate_all_and_draw() {
    /*
        this will generate all possible winning states,
        and check if state.utility() returns correctly
        that it's a win
        however, NOTE that generating all winning
        states does not necessarily guarantee that
        state.utility() is completely correct,
        because state.utility() also depends
        on the value of state.last_move,
        so to completely test all the possible cases,
        you also need to generate all winning states,
        and for each state, generate all possible
        last moves (out of 4 possible moves),
        i.e. change the last piece inserted into the
        board by changing state.last_move,
        but this will also generate impossible last_moves
        for example: when winning by 4 in a single column,
        the only possible move is to put the piece on the
        very top.
    */
    for (int last_move=1; last_move<=4; ++last_move) {
        cout << endl;
        cout << "> last piece is: " << last_move << endl;
        cout << "-------------------------" << endl << endl;
        // rows
        vector<State> win_rows = generate_win_rows(last_move);
        cout << "# win rows: " << win_rows.size() << endl;
        cout << "==========================" << endl;
        for(auto state: win_rows) {
            piece state_util = state.utility();
            //print only states with wrong utility
            if (state_util != fill_piece) {
                cout << "state utility: " << state.utility() << endl;
                print_board(state);
            }
        }
        // cols
        vector<State> win_cols = generate_win_cols(last_move);
        cout << "# win cols: " << win_cols.size() << endl;
        cout << "==========================" << endl;
        for(auto state: win_cols) {
            piece state_util = state.utility();
            //print only states with wrong utility
            if (state_util != fill_piece) {
                cout << "state utility: " << state.utility() << endl;
                print_board(state);
            }
        }
        // 45 diagonals
        vector<State> win_45 = generate_win_45(last_move);
        cout << "# win 45 degree diagonals: " << win_45.size() << endl;
        cout << "==========================" << endl;
        for(auto state: win_45) {
            piece state_util = state.utility();
            //print only states with wrong utility
            if (state_util != fill_piece) {
                cout << "state utility: " << state.utility() << endl;
                print_board(state);
            }
        }
        // 135 diagonals
        vector<State> win_135 = generate_win_135(last_move);
        cout << "# win 45 degree diagonals: " << win_135.size() << endl;
        cout << "==========================" << endl;
        for(auto state: win_135) {
            piece state_util = state.utility();
            //print only states with wrong utility
            if (state_util != fill_piece) {
                cout << "state utility: " << state.utility() << endl;
                print_board(state);
            }
        }
    }
    
}
