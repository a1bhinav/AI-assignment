#include <bits/stdc++.h>

using namespace std;

//int number_of_nodes=0;

struct state{

	int starting_node;

	int cost;

	int heursitic_cost;

	vector <int> node_list;

	//int num_nodes;

	vector <state*> children;

};

typedef struct state state;

vector <state*> open_list;

vector <state*> closed_list;

int calc_heurisitics(state* s,vector <vector <int> > &ct,int no)
{
	if(s->node_list.size()>=1)
	{
		int start=s->starting_node;

		int num=no;

		int a[num];

		a[0]=1;

/*		for(int i=0;i<s->node_list.size();i++)
		{
			cout<<s->node_list[i]<<" ";
		}
		cout<<"\n";
*/
		for(int i=1;i<num;i++)
		{
			a[i]=0;
		}

		for(int i=0;i<s->node_list.size();i++)
		{
			a[s->node_list[i]]=1;
		}

		int curr_node=s->node_list[s->node_list.size()-1];

//		cout<<"heur\n";		

		vector <vector <int> > b;
	
		int remain=no-s->node_list.size();

		while(1)
		{
			int count=0;
		//	int remain=no-s->node_list.size();

			b.resize(0);

//			cout<<"\n";

			for(int i=0;i<num;i++)
			{
				if(a[i]==0)
				{

					count++;

					b.resize(count);

					b[count-1].push_back(ct[curr_node][i]);
					b[count-1].push_back(i);
				}
			}
				
//			cout<<"here!!\n";
			
			if(b.size()!=0)
			{

				sort(b.begin(),b.end());
			

//				cout<<"too!\n";

		//		cout<<b.size()<<"\n";

				s->heursitic_cost +=b[0][0];
			
			//	cout<<"t!!\n";

				a[b[0][1]]=1;

			//	cout<<"ii!!\n";

				remain--;
				
				curr_node=b[0][1];
			
		

				if(remain==0)
				{
					s->heursitic_cost +=ct[curr_node][0];

					break;
				}	
			
			}

			if(b.size()==0)
			{

				s->heursitic_cost +=ct[curr_node][0];

				break;
			}
		}

	}

	return s->heursitic_cost;

}

state* state_init(vector <vector <int> > &ct,int no,int node)
{
	state* start=NULL;

	start=(state*) malloc(sizeof(state));

	start->starting_node=node;

	start->cost=0;

	start->heursitic_cost=0;

	start->node_list.push_back(node);

	calc_heurisitics(start,ct,no);

	return start;

}

int goal_test(state* s,int no)
{
  int	flag=0;

	if(s->node_list.size()<no)
	{
		return 0;
	}
	else
	{
		if(s->node_list.size()==no)
		{
			
			flag=1;
		}
	}
		
	//Add code to check if redudant nodes are filled to satisfy the s->node_list==no condition

	return flag;
}


void print_tour(state* s)
{
	for(int i=0;i<s->node_list.size();i++)
	{
		cout<<s->node_list[i]<<" ";
	}

	cout<<"\n";	

}

int main()
{
	int number_nodes;

	cout<<"Enter the number of nodes\n";

	cin>>number_nodes;

	//number_of_nodes=number_nodes;

	vector <vector <int> > cost_table;

	cost_table.resize(number_nodes);

	for(int i=0;i<number_nodes;i++)
	{
		cost_table[i].resize(number_nodes);
	}

	cout<<"Enter the cost of each path between the tables with starting state being marked with number 0\nSelf distance will be assigned -1\n";

	for(int i=0;i<number_nodes;i++)
	{
		for(int j=0;j<number_nodes;j++)
		{
			cin>>cost_table[i][j];
		}
	}

	cout<<"\n";

	for(int i=0;i<number_nodes;i++)
	{
		for(int j=0;j<number_nodes;j++)
		{
			cout<<cost_table[i][j]<<" ";
		}
		cout<<"\n";
	}

	state* start=state_init(cost_table,number_nodes,0);
	
	cout<<"\n"<<start->heursitic_cost<<"\n";

	open_list.push_back(start);
	
	int flag=1;
	
	int y=0;

	while(flag)
	{
//		cout<<++y<<"\n";

		state* temp=open_list[0];

		cout<<"cost "<<temp->cost<<"\n";

		flag=goal_test(temp,number_nodes);

	//	cout<<"y: "<<y<<"flag: "<<flag<<"\n";

		if(flag==1)
		{
			cout<<"Found Solution\n";

		//	temp->node_list.push_back(temp->starting_node);

		//	temp->cost = temp->cost +cost_table[temp->node_list[temp->node_list.size()-1]][0];

		//	print_tour(temp);

//			cout<<"cost: "<<temp->cost<<"\n";

			closed_list.push_back(temp);

			open_list.erase(open_list.begin());

			temp->node_list.push_back(temp->starting_node);

			print_tour(temp);

			int last_node=temp->node_list[number_nodes-1];

			cout<<"Final cost: "<<temp->cost+cost_table[last_node][0]<<"\n";

			break;
		}
		else
		{
		//	cout<<"number_nodes "<<number_nodes<<"\n";

			for(int i=0;i<temp->node_list.size();i++)
			{
				cout<<temp->node_list[i]<<" ";
			}
			cout<<"\n";



			if(temp->node_list.size() < number_nodes)
			{
				int a[number_nodes];

				for(int i=0;i<number_nodes;i++)
				{
					a[i]=0;
				}

				for(int i=0;i<temp->node_list.size();i++)
				{
					a[temp->node_list[i]]=1;
				}

/*				for(int i=0;i<number_nodes;i++)
				{
					cout<<a[i]<<" ";
				}
				cout<<"\n";
*/
				for(int i=0;i<number_nodes;i++)
				{
					if(a[i]==0)
					{
						state* temp1=(state*) malloc(sizeof(state));

						temp1->starting_node=temp->starting_node;

						for(int j=0;j<temp->node_list.size();j++)
						{
							temp1->node_list.push_back(temp->node_list[j]);
						}

						temp1->node_list.push_back(i);

		temp1->cost=temp->cost+cost_table[temp1->node_list[temp1->node_list.size()-1]][temp1->node_list[temp1->node_list.size()-2]];				

						calc_heurisitics(temp1,cost_table,number_nodes);

//						cout<<"before\n";	

						temp->children.push_back(temp1);

						open_list.push_back(temp1);

					}
				}
			}

//			cout<<"Reached here!!\n";

			closed_list.push_back(temp);

			open_list.erase(open_list.begin());

			if(open_list.size()==0)
			{
				break;
			}

			
			int min=open_list[0]->cost+open_list[0]->heursitic_cost;

			for(int i=1;i<open_list.size();i++)
			{
				int c=open_list[i]->cost+open_list[i]->heursitic_cost;

				if(c < min)
				{
					min=c;					
				}
			}


			vector <vector <int> > temp_list;

			int cot=0;

			for(int i=0;i<open_list.size();i++)
			{
				if((open_list[i]->cost+open_list[i]->heursitic_cost)==min)
				{
					cot++;

					temp_list.resize(cot);

					temp_list[cot-1].push_back(open_list[i]->cost);

					temp_list[cot-1].push_back(i);
				}
			}


			sort(temp_list.begin(),temp_list.end());

			state* tp=open_list[temp_list[0][1]];

			open_list[temp_list[0][1]]=open_list[0];

			open_list[0]=tp;
			
			flag=1;
			
		}
	}

	return 0;
}

		
