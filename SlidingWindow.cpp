#include <iostream>
#include <string.h>
using namespace std;

int main(){
	char receiver[100];
	int win_s,i=0;
	string send;
	cout<<"Enter the window size:\n";
	cin>>win_s;
	cin.ignore();
	cout<<"Enter the data to be sent:";
	getline(cin,send,'\n');
	while(send[i]!='\0'){
		i++;
	}
	
	if(i<win_s)
	{	int a=win_s-i;
		cout<<"Window size shrinked by	"<<a<<"\n";
		win_s=win_s-a;
	}
	else if(i>win_s)
	{
		int a=i-win_s;
		cout<<"Window size expanded by	"<<a<<"\n";
		win_s=win_s+a;
	}
	else if(i==win_s)
	{
		cout<<"No need to change window size\n";
	}


	for(int j=0;j<i;j++){
		receiver[j]=send[j];
	}
	//receiver[j]=NULL;
	cout<<"Data sent successfully by sender!\n\n\n";
	
	cout<<"Data received by receiver-	\n";
	for(int i=0;i<win_s;i++)
	{
		cout<<receiver[i];	
	}	
	cout<<"\n";
	return 0;
}
