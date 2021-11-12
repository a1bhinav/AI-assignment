#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
#include "game_structure.h"
#include "AI.h"
using namespace std;



int toss()
{
	srand(time(NULL));

	int l = rand() % 53;

	if(l%2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int call_player(int turn_number,game* platform)
{
	turn_number = turn_number % 2;

	switch(turn_number)
	{
		case 1: {

				if(platform->first_turn_taken_by==1)
				{
					cout<<"Player1: ";
					int temp=AI(platform);
					platform->current_turn=1;
					if(temp==0)
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					int temp1;

					if(platform->game_mode==1)
					{
						cout<<"Player1: ";
						temp1=AI(platform);
					}
					else
					{
						cout<<"Number of sticks you want to remove: ";
						int temp;
						while(1)
						{
							cin>>temp;
							if(temp > platform->remaining_sticks || (temp > 3))
							{
								cout<<"Can't remove "<<temp<<" sticks, not available\n";
								cout<<"Please remove correct number of sticks!\n";
								cout<<"Number of sticks you want to remove: ";
							}
							else
							{
								platform->remaining_sticks -=temp;
								break;
							}
						}

						temp1=1;
					}

					platform->current_turn=2;

					if(temp1==0)
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
			
		}

		break;

		case 0: {

					int temp1;
					if(platform->first_turn_taken_by==1)
					{
						if(platform->game_mode==1)
						{
							cout<<"Player2: ";
							temp1=AI(platform);
						}
						else
						{
							cout<<"Number of sticks you want to remove: ";
							int temp;
							while(1)
							{
								cin>>temp;
								if(temp > platform->remaining_sticks || (temp > 3))
								{
									cout<<"Can't remove "<<temp<<" sticks, not available\n";
									cout<<"Please remove correct number of sticks!\n";
									cout<<"Number of sticks you want to remove: ";
								}
								else
								{
									platform->remaining_sticks -=temp;
									break;
								}
							}

							temp1 = 1;
						}

						platform->current_turn=2;
						if(temp1==0)
						{
							return 0;
						}
						else
						{
							return 1;
						}
					}
					else
					{
						cout<<"Player2: ";
						int temp=AI(platform);
						platform->current_turn=1;
						if(temp==0)
						{
							return 0;
						}
						else
						{
							return 1;
						}
					}

		} 
	}
}

void increment_turn(game* platform)
{
	platform->turn_number++;
}

int main()
{
	int toss_result;

	game platform;

	cout<<"Enter the total number of sticks: ";
	cin>>platform.total_stick_count;
	cout<<"\n";

	platform.remaining_sticks=platform.total_stick_count;

	cout<<"Player 1 is the AI\n";

	cout<<"Select the game mode:\n";

	cout<<"1. AI vs AI\n";
	cout<<"2. AI vs Human\n";

	cout<<"Enter the game mode: ";
	cin>>platform.game_mode;
	cout<<"\n";

	int temp;
	cout<<"TOSS....\n";
	if(platform.game_mode==2)
	{
		cout<<"HEADS or TAILS: Enter 0 for HEADS and 1 for TAILS: ";
		cin>>temp;
	}

	if(platform.game_mode==1)
	{
		srand(time(NULL));
		temp=rand() % 2;

		if(temp==0)
		{
			cout<<"Player 2 (AI) chooses HEAD\n";
		}
		else
		{
			cout<<"Player 2 (AI) chooses TAIL\n";
		}
	}

	cout<<"Flipping the coin.....\n";

	sleep(3);

	toss_result=toss();

	if(toss_result==0)
	{
		cout<<"It's HEADS\n";
		if(temp==0)
		{
			cout<<"You won the toss\nYou will play the first turn\n";
			platform.first_turn_taken_by=2;
			platform.current_turn=platform.first_turn_taken_by;
		}
		else
		{
			cout<<"You lose the toss\nAI (Player 1) will play the first turn\n";
			platform.first_turn_taken_by=1;
			platform.current_turn=platform.first_turn_taken_by;
		}
	}
	else
	{
		cout<<"It's TAILS\n";

		if(temp==1)
		{
			cout<<"You won the toss\nYou will play the first turn\n";
			platform.first_turn_taken_by=2;
			platform.current_turn = platform.first_turn_taken_by;
		}
		else
		{
			cout<<"You lose the toss\nAI (Player 1) will play the first turn\n";
			platform.first_turn_taken_by=1;
			platform.current_turn = platform.first_turn_taken_by;
		}
	}

	platform.turn_number=1;

	while(platform.remaining_sticks!=0)
	{
		cout<<"Remaining Sticks: "<<platform.remaining_sticks<<"\n";
		int terminate=call_player(platform.turn_number,&platform);
		if(terminate==0 && platform.game_mode==1)
		{
			break;
		}
		increment_turn(&platform);
	}

	if(platform.current_turn==platform.first_turn_taken_by)
	{
		if(platform.remaining_sticks==0)
		cout<<"Second Player Wins\n";
		else
		{
			 cout<<"First Player Resigns (Accepts Defeat)\n";
			 cout<<"Second Player Wins\n";
		}

	}
	else
	{	
		if(platform.remaining_sticks==0)
		cout<<"First Player Wins\n";
		else
		{
			cout<<"Second Player Resigns (Accept Defeat)\n";
			cout<<"First Player Wins\n";
		}
	}

	return 0;
}
