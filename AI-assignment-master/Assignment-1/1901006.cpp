#include <bits/stdc++.h>

using namespace std;

struct board{
		int board[8][8];

		int queen_pos[8];

		int cost;

		int queen_count;

		vector <struct board*> children;

	    };


typedef struct board board;

board* initial_state= (board*) malloc(sizeof(board));


void init(board* b)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			b->board[i][j]=0;
		}
	}


	for(int i=0;i<8;i++)
	{
		b->queen_pos[i] = -1;
	}

	b->cost=0;

	b->queen_count=0;

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
		//	cout<<"hey\n";
			cout<<b->board[i][j]<<" ";
		}

		cout<<"\n";
	}

	cout<<"\n";
}


vector <struct board* > que;



int goal_test(board* b)
{
	int flag=1;

	for(int i=0;i<8;i++)
	{
		if(b->queen_pos[i]==-1)
		{
			flag=0;
			return flag;
		}
	}

	for(int i=0;i<8;i++)   //check for if any two queens are in the same column
	{
		for(int j=i+1;j<8;j++)
		{
			if(b->queen_pos[i]==b->queen_pos[j])
			{
				flag=0;
				return flag;
			}
		}
	}

	for(int i=0;i<7;i++) 
	{
		int temp=b->queen_pos[i];

		for(int j=i+1;j<8;j++)
		{
			temp++;

			if(temp<8)
			{
				if(b->board[j][temp]==1)
				{
					flag=0;
					return flag;
				}
			}
			else
			{
				break;
			}
		}

		temp = b->queen_pos[i];

		for(int j=i+1;j<8;j++)
		{
			temp--;

			if(temp>=0)
			{
				if(b->board[j][temp]==1)
				{
					flag=0;
					return flag;
				}
			}
			else
			{
				break;
			}

		}
	}

	return flag;

}


void print_solution(board* b)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<b->board[i][j]<<" ";
		}

		cout<<"\n";
	}

	cout<<"\n";
}

int find_min_cost(vector <struct board*> b)
{
	int min = b[0]->cost;

	int index=0;

	for(int i=1;i<b.size();i++)
	{
		if(b[i]->cost<min)
		{
			min=b[i]->cost;
			index=i;
		}
	}

	return index;

}

int interm_column_check(board* b,int i)
{
	int flag=1;

	for(int j=0;j<b->queen_count;j++)
	{
		if(b->queen_pos[j]==i)
		{

			flag=0;
			break;
		}
	}

	return flag;
}

int interm_diagonal_check(board* b,int i)
{
	int flag=1;

	int row=b->queen_count-1;
	
	int temp=i;


	for(int j=row;j>=0;j--)
	{
		temp++;

		if(temp<8)
		{	
			if(b->board[j][temp]==1)
			{
				flag=0;
				break;
			}
		}
		else
		{
			break;
		}
	}

	temp =i;
	for(int j=row;j>=0;j--)
	{
		temp--;

		if(temp >= 0)
		{
			if(b->board[j][temp] == 1)
			{
				flag=0;

				break;
			}
		}
		else
		{
			break;
		}
	}

	temp=i;

	for(int j=row;j<8;j++)
	{
		temp++;

		if(temp < 8)
		{
			if(b->board[j][temp] == 1)
			{	
				flag=0;

				break;
			}
		}
		else
		{
			break;
		}
	}

	
	temp = i;

	for(int j=row;j<8;j++)
	{
		temp--;

		if(temp >=0)
		{
			if(b->board[j][temp] == 1)
			{
				flag=0;

				break;
			}
		}
		else
		{
			break;
		}
	}

	return flag;
}
				

int main()
{
	init(initial_state);

	int flag= goal_test(initial_state);

	que.push_back(initial_state);

	int soln = 0;

	while(!flag)
	{
		if(que[0]->queen_count<=8)
		{
			for(int i=0;i<8;i++)
			{

				int flag1=interm_column_check(que[0],i);
				
				if(flag1==0)
				{
				//	cout<<flag<<"\n";
					continue;
				}

				flag1 = interm_diagonal_check(que[0],i);

				if(flag1==0)
				{
				//	cout<<flag<<"\n";
					continue;
				}
				

		
				board* temp = (board*) malloc(sizeof(board));

				for(int p=0;p<que[0]->queen_count;p++)
				{
					 temp->queen_pos[p]=que[0]->queen_pos[p];
				}

				for(int p=que[0]->queen_count;p<8;p++)
				{
					temp->queen_pos[p]=-1;
				}

				for(int p=0;p<8;p++)
				{
					for(int r=0;r<8;r++)
					{
						temp->board[p][r]=0;					
					}
				}

				temp->queen_pos[que[0]->queen_count]=i;

			//	temp->board[que[0]->queen_count][i]=1;

				temp->cost=que[0]->cost+1;

				temp->queen_count=que[0]->queen_count+1;

				for(int r=0;r<temp->queen_count;r++)
				{
					temp->board[r][temp->queen_pos[r]]=1;
				}

				que[0]->children.push_back(temp);

				que.push_back(temp);

			//	free(temp);
			}

			flag=goal_test(que[0]);

			//cout<<flag<<"\n";

			if(flag==1)
			{
				soln++;

				cout<<"solution "<<soln<<"\n";
				cout<<endl;
				print_solution(que[0]);
				flag=0;
			}
			
			//board* rem=que[0];

			que.erase(que.begin());

			if(que.empty())
			{
				//cout<<"empty\n";
				break;
			}

	
			//free(rem);

			int index = find_min_cost(que);

			board* temp = que[index];

			que[index]=que[0];

			que[0]=temp;

		//	print_solution(que[0]);

		}
		else
		{
			flag=goal_test(que[0]);

			if(flag==1)
			{
				print_solution(que[0]);
				flag=0;
			}
			
			//board* rem = que[0];

			que.erase(que.begin());
	
			if(que.empty())
			{
				break;
			}

			//free(rem);

			int index= find_min_cost(que);

			board* temp= que[index];

			que[index]=que[0];

			que[0]=temp;

		//	print_solution(que[0]);
		}		
	}

	return 0;
}

