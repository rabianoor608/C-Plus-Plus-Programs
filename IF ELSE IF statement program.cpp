#include<iostream>
using namespace std;
int main()
{
	int score;
	cout<<"Enter a score:";
	cin>>score;
	if(score>=90)
	cout<<"Grade=A"<<endl;
	else if(score>=80)
	cout<<"Grade=B"<<endl;
	else if(score>=70)
	cout<<"Grade=C"<<endl;
	else if(score>=60)
	cout<<"Grade=D"<<endl;
	else if(score>=50)
	cout<<"Grade=E"<<endl;
	else
	cout<<"Grade=F"<<endl;
	return 0;
}
