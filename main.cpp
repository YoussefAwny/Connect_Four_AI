#include <iostream>
#include "state.h"
#include "abs.h"
using namespace std;


//Function to print the board
void print_board (State s)
{
	for (int i = BOARD_ROWS -1 ; i>=0 ; i--)
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


/*for testing*/


State* abs ( State* S)
{
	(*(S)).make_move((piece)us, 0 ,S );

	return S;
}




/*for testing */



int main ()
{
	char c;			//char to decide who would begin the game
	piece player = them;		//any inserted move is from them


	cout<<"If you want to play first type f and type any other key to play second: ";
	cin>>c;

	State *s = new State() ;	//State to Start with


	//in case the human starts
	if(c=='f')
	{
		print_board (*(s));

		int col;
		cout<<"Enter Column number you want to insert in : ";
		cin>>col;


		//column value out fo range
		while (col<1 || col>7)
		{
			cout<<endl;
			cout<<"please enter the value of the Col between 1 and 7";
			cout<<endl<<endl<<endl;
			cout<<"Enter Col number you want to insert in : ";
			cin>>col;
		}
		

		//Make the move the human entered
		bool check=(*(s)).make_move(player,col-1, s);

		print_board(*(s));

		
	}

	bool draw = true;
	
	while  (!(*(s)).is_full())
	{

		draw= false;
		
		*(s) = alpha_beta_search(*(s));		//Make the computer move
		
		print_board(*(s));
		
		//print_board (next);
		
		

		//for testing
		
	//	s = abs (s);
		

		
		if ((*(s)).utility()==(piece) us)
		{
			cout<<endl;
			cout<< "You Lost"<<endl;;
			break;
		}


		int col;
		cout<<"Enter Column number you want to insert in : ";
		cin>>col;

		//check if col value out of range
		while (col<1 || col>7)
		{
			cout<<endl;
			cout<<"please enter the value of the Col between 1 and 7";
			cout<<endl<<endl<<endl;
			cout<<"Enter Col number you want to insert in : ";
			cin>>col;
		}


		//Make the move human entered
		bool check=(*(s)).make_move(player,col-1, s);

		//Check if row is full
		if (check)
		{
			print_board(*(s));
		}
		
		else 
		{
			while (!check)
			{
				cout<<endl;
				cout<<"Column is full enter another Column Number";
				cout<<endl<<endl<<endl;
				cout<<"Enter Col number you want to insert in : ";
				cin>>col;
				check=(*(s)).make_move(player,col-1, s);
			}
		}

		if ((*(s)).utility()==(piece)them)
		{
			cout<<endl;
			cout<< "You Won"<<endl;;
			break;
		}

		draw=true;

	}

	if(draw)
	{
		cout<<endl;
		cout<<"Draw";
	}



}