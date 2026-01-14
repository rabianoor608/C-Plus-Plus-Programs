#include<iostream>
using namespace std;
char arr[9];
void initializer()
{
	for(int i=0; i<9; i++)
	{
		arr[i] = '.';
	}
}
void table()
{
	cout<<"\n\n\t\t Welcome to Tik Tak Toe Game"<<endl;
	cout<<"\n\n\n";
	cout<<"\t\t\t"<<arr[0]<<" | "<<arr[1]<<" | "<<arr[2]<<"\n";
	cout<<"\t\t\t---------\n";
	cout<<"\t\t\t"<<arr[3]<<" | "<<arr[4]<<" | "<<arr[5]<<"\n";
	cout<<"\t\t\t---------\n";
	cout<<"\t\t\t"<<arr[6]<<" | "<<arr[7]<<" | "<<arr[8]<<"\n";
}
bool empty_check(int box)
{
	return arr[box]=='.';
}
bool draw()
{
	int counter =0;
	for(int i=0; i<9; i++)
	{
		if(arr[i] != '.')
		{
			counter++;
		}
	}
	if(counter==9)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool win_check()
{
	for(int i=0; i<9; i=i+3)
	{
		if((arr[i]=='O'&& arr[i+1]=='O'&& arr[i+2]=='O') || (arr[i]=='X'&& arr[i+1]=='X'&& arr[i+2]=='X'))
		{
			return true;
		}
		
	}
	for(int i=0; i<3; i++)
	{
		if((arr[i]=='O'&& arr[i+3]=='O'&& arr[i+6]=='O') || (arr[i]=='X'&& arr[i+3]=='X'&& arr[i+6]=='X'))
		{
			return true;
		}
	}
	if((arr[0]=='O'&& arr[4]=='O'&& arr[8]=='O') || (arr[0]=='X'&& arr[4]=='X'&& arr[8]=='X'))
	{
		return true;
	}
	if((arr[2]=='O'&& arr[4]=='O'&& arr[6]=='O') || (arr[2]=='X'&& arr[4]=='X'&& arr[6]=='X'))
	{
		return true;
	}
	return false;
}
int main()
{
	int box, player=1;
	initializer();
	while(!win_check())
	{
		table();
		cout<<"\n\n\t\t Player "<<player<<" Select box\n";
		cin>>box;
		if(empty_check(box-1))
		{
		   if(player == 1)
		   {
			  arr[box-1] = 'X';
		  	  player = 2;
		   }
		   else if(player == 2)
		   {
			  arr[box-1] = 'O';
			  player = 1;
		   }
		}
		system("cls");
		if(draw())
		{
			cout<< "Draw\n\n\n";
			return 0;
		}
	}
	if(player==1)
	{
		player = 2;
	}
	else
	{
		player = 1;
	}
	cout<<"Player " <<player<<" win\n\n\n";
	return 0;
}

