#include <iostream>
#include "state.h"
using namespace std;

void print_board (State s)
{
	for (int i = 0 ; i<BOARD_ROWS ; i++)
		{
			for (int j=0 ; j<BOARD_COLS ; j++ )
			{
				if(s.board[i][j]==-1)
					cout<<"2";
				else
				cout<<s.board[i][j];
				cout<<"\t";
			}
			cout<<endl;
		}
}

int main ()
{
	char c;
	piece player;
	cout<<"if you want to play first type f and type any other key to play second: ";

	cin>>c;

	State s ;

	if(c=='f')
	{
		

		print_board (s);

		int col;
		cout<<"Enter Col number you want to insert in : ";
		cin>>col;
		player= them;
		State next=s.make_move(player,col);

		print_board(next);
		

		
	}


	while  (!s.isfull)
	{
		State next = dfs(s);
		print_board(next);
		int col;
		cout<<"Enter Col number you want to insert in : ";
		cin>>col;
		player= them;
		State after_next=s.make_move(player,col);
		print_board(after_next);
	}



}