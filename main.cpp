#include <iostream>
#include "state.h"
using namespace std;


//Function to print the board
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

	cout<<endl<<endl;
}




int main ()
{
	char c;			//char to decide who would begin the game
	piece player = them;		//any inserted move is from them


	cout<<"if you want to play first type f and type any other key to play second: ";
	cin>>c;

	State *s = new State() ;	//State to Start with


	//in case the human starts
	if(c=='f')
	{
		print_board (*(s));

		int col;
		cout<<"Enter Col number you want to insert in : ";
		cin>>col;


		//col value out fo range
		if (col<1 || col>7)
		{
			cout<<endl;
			cout<<"please enter the value of the Col between 1 and 7";
			cout<<endl<<endl<<endl;
			cout<<"Enter Col number you want to insert in : ";
			cin>>col;
		}
		

		//Make the move the human entered
		bool check=(*(s)).make_move(player,col, s);

		//Check if row is full
		if (check)
		{
			print_board(*(s));
		}
		
		else 
		{
			cout<<endl;
			cout<<"Full Col";
			cout<<endl<<endl<<endl;
		}

	


		
	}

	
	while  (!(*(s)).is_full())
	{

		State* next = abs(s);		//Make the computer move
		print_board(*(next));
		
		if ((*(s)).utility()==1)
		{
			cout<<endl;
			cout<< "You Lost";
			break;
		}

		int col;
		cout<<"Enter Col number you want to insert in : ";
		cin>>col;

		//check if col value out of range
		if (col<1 || col>7)
		{
			cout<<endl;
			cout<<"please enter the value of the Col between 1 and 7";
			cout<<endl<<endl<<endl;
			cout<<"Enter Col number you want to insert in : ";
			cin>>col;
		}


		//Make the move human asked for
		//Make the move the human entered
		bool check=(*(next)).make_move(player,col, next);

		//Check if row is full
		if (check)
		{
			print_board(*(next));
		}
		
		else 
		{
			cout<<endl;
			cout<<"Full Col";
			cout<<endl<<endl<<endl;
		}

		if ((*(s)).utility()==-1)
		{
			cout<<endl;
			cout<< "You Won";
			break;
		}

	}



}