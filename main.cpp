#include <iostream>
#include "state.h"
using namespace std;



int main ()
{
	char c;
	piece player;
	cout<<"if you want to play first type f and type any other key to play second: ";

	cin>>c;

	if(c=='f')
	{
		State s ;

		for (int i = 0 ; i<BOARD_ROWS ; i++)
		{
			for (int j=0 ; j<BOARD_COLS ; j++ )
			{
				cout<<s.board[i][j];
				cout<<"\t";
			}
			cout<<endl;
		}

		int col;
		cout<<"Enter Col number you want to insert in : ";
		cin>>col;
		player= them;
		State next=s.make_move(player,col);

		
		for (int i = 0 ; i<BOARD_ROWS ; i++)
		{
			for (int j=0 ; j<BOARD_COLS ; j++ )
			{
				cout<<next.board[i][j];
				cout<<"\t";
			}
			cout<<endl;
		}

		
	}
}