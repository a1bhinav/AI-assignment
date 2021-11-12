#include <bits/stdc++.h>
using namespace std;

struct population
{
	int population_size;

	vector <vector <int> > cluster_list;

	vector <int> fitness_value;
};

typedef struct population population;

void initial_population(population* populi,int n,int m,int k,int size)
{
	srand(time(NULL));

	populi->population_size=size;

	populi->cluster_list.resize(populi->population_size);

	for(int i=0;i<populi->population_size;i++)
	{
		populi->cluster_list[i].resize(n);	
	}

	for(int i=0;i<populi->population_size;i++)
	{



		vector <int> check;

		check.resize(k,0);

		for(int j=0;j<n;j++)
		{
			

			populi->cluster_list[i][j]=rand() % k;

		}

		int count=0;

		for(int l=0;l<n;l++)
		{
			check[populi->cluster_list[i][l]]++;
		}

		for(int l=0;l<k;l++)
		{
			if(check[l]==0)
			{
				populi->cluster_list[i][count]=l;
				count++;
			}
		}

	}


}


void show_population(population* populi)
{
	for(int i=0;i<populi->population_size;i++)
	{
		for(int j=0;j<populi->cluster_list[i].size();j++)
		{
			cout<<populi->cluster_list[i][j]<<" ";
		}
		cout<<"\n";
	}
}


void fitness_function(population* populi,int n,int m,int k,vector <vector <int> > arr)
{
	populi->fitness_value.resize(populi->population_size,0);

	for(int i=0;i<populi->population_size;i++)
	{
		for(int j=0;j<k;j++)
		{
			vector <int> temp;

			for(int l=0;l<n;l++)
			{
				if(populi->cluster_list[i][l]==j)
				{
					temp.push_back(l);
				}
			}

			int sum=0;

			for(int l=0;l<temp.size();l+=1)
			{
				int add=0;

				if((l+1)<temp.size())
				{
					if(temp.size()!=1)
					{
						for(int t=0;t<m;t++)
						{
							add=add + abs(arr[temp[l+1]][t] -arr[temp[l]][t]);
						}
					}

					sum=sum+add;
				}
				else
				{
					break;
				}
			}

			populi->fitness_value[i]=populi->fitness_value[i]+sum;
		}
	}
}


void show_fitness(population* populi)
{
	for(int i=0;i<populi->fitness_value.size();i++)
	{
		cout<<populi->fitness_value[i]<<" ";
	}

	cout<<"\n";
}

bool sortcol( const vector<int>& v1, const vector<int>& v2 )
{ 
 return v1[v1.size()-1] < v2[v2.size()-1]; 
} 

void sort_population(population* populi)
{
	for(int i=0;i<populi->population_size;i++)
	{
		populi->cluster_list[i].push_back(populi->fitness_value[i]);
	}

	sort(populi->cluster_list.begin(),populi->cluster_list.end(),sortcol);

	for(int i=0;i<populi->population_size;i++)
	{
		populi->cluster_list[i].pop_back();
	}
}

population crossover(population* populi,int number_of_students,int m,int k,vector<vector <int> > arr)
{
	population crossover_population;

	int crossover_point = rand()% number_of_students;

	cout<<"crossover point is "<<crossover_point<<"\n";

	crossover_population.cluster_list.resize(populi->population_size);
	crossover_population.population_size = populi->population_size;

	//cout<<"\ntest1....\n";

	for(int i=0;i<populi->population_size;i+=2)
	{
		//cout<<"test2"<<" "<<i<<"\n";
		if((i+1)<populi->population_size)
		{
			//cout<<"entered...\n";
			for(int j=0;j<=crossover_point;j++)
			{
				crossover_population.cluster_list[i].push_back(populi->cluster_list[i+1][j]);
				crossover_population.cluster_list[i+1].push_back(populi->cluster_list[i][j]);
			}

			//cout<<"test3\n";

			for(int j=crossover_point+1;j<number_of_students;j++)
			{
				crossover_population.cluster_list[i].push_back(populi->cluster_list[i][j]);
				crossover_population.cluster_list[i+1].push_back(populi->cluster_list[i+1][j]);
			}

			//cout<<"test4\n";
		}

		if(i == populi->population_size - 1)
		{
			for(int j=0;j<number_of_students;j++)
			{
				crossover_population.cluster_list[i].push_back(populi->cluster_list[i][j]);
			}
		}
	}

	//cout<<"got out\n";

	fitness_function(&crossover_population,number_of_students,m,k,arr);

	//cout<<"Evaluation done...\n";

	sort_population(&crossover_population);

	return crossover_population;
}


void mutation(population* populi,int n,int k)
{

	cout<<"\nMUTATION HAPPENING....\n";

	for(int i=0;i<populi->population_size/2;i++)
	{
		int population_number = rand() % populi->population_size;

		int student_number1 = rand() % n;

		int student_number2 = rand() % n;

		int temp = populi->cluster_list[population_number][student_number1];

		populi->cluster_list[population_number][student_number1] = populi->cluster_list[population_number][student_number2];

		populi->cluster_list[population_number][student_number2] = temp;

	}
}

int main()
{

	int n,m,k;

	cout<<"Enter the number of students\n";

	cin>>n;

	cout<<"Enter the number of subjects\n";

	cin>>m;

	cout<<"Enter the number of groups you want to have\n";

	cin>>k;

	vector <vector <int> > arr;

	arr.resize(n);

	for(int i=0;i<n;i++)
	{
		arr[i].resize(m);
	}

	for(int i=0;i<n;i++)
	{
		cout<<"Enter the marks of "<<i+1<<"th student\n";

		for(int j=0;j<m;j++)
		{
			cin>>arr[i][j];
		}
	}

	population populi;

	initial_population(&populi,n,m,k,5);

	show_population(&populi);

	cout<<"\nCalculating fitness value.....";

	fitness_function(&populi,n,m,k,arr);

	cout<<"\n Showing fitness value\n";

	show_fitness(&populi);

	sort_population(&populi);

	sort(populi.fitness_value.begin(),populi.fitness_value.end());

	population crossover_population;

	crossover_population=crossover(&populi,n,m,k,arr);

	cout<<"Crossover Complete...\n";

	show_population(&crossover_population);

	sort(crossover_population.fitness_value.begin(),crossover_population. fitness_value.end());

	show_fitness(&crossover_population);


	bool selection_done=true;

	int tick=1;

	

	while(selection_done)
	{
		selection_done=false;
		for(int i=0;i<crossover_population.population_size;i++)
		{
			int status=0;

			for(int j=0;j<populi.population_size;j++)
			{
				if(crossover_population.fitness_value[i]<populi.fitness_value[j])
				{
					selection_done=true;
					status=1;

					for(int t=j;t<populi.population_size-1;t++)
					{
						for(int f=0;f<m;f++)
						{
							populi.cluster_list[t+1][f]=populi.cluster_list[t][f];
						}

						populi.fitness_value[t+1]=populi.fitness_value[t];
					}

					for(int f=0;f<m;f++)
					{
						populi.cluster_list[j][f]=crossover_population.cluster_list[i][f];
					}

					populi.fitness_value[j]=crossover_population.fitness_value[i];
					break;
				}
			}

			if(status==0)
			{
				break;
			}
		}

		if(selection_done==false)
		{
			break;
		}

		//free(&crossover_population);

		if(tick%4 == 0)
		{
			mutation(&populi,n,k);

			fitness_function(&populi,n,m,k,arr);
		}



		sort_population(&populi);

		sort(populi.fitness_value.begin(),populi.fitness_value.end());

		crossover_population=crossover(&populi,n,m,k,arr);
		cout<<"Crossover Complete...\n";

		sort(crossover_population.fitness_value.begin(),crossover_population. fitness_value.end());

		tick++;

	}

	cout<<"COMPLETED IN tick: "<<tick<<"\n";

	cout<<"FINAL POPULATION:\n";

	show_population(&populi);

	cout<<"Fitness Value:\n";

	show_fitness(&populi);

	
	return 0;
}
