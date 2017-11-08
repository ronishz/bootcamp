#include<iostream>
#include<string>
using namespace std;

class aproiri{
	public:
		string ls[11]={"Mango","Onion","Apple","Corn","Eggs","Chocolate","Nuts","Keychain","Knife","Jar","Toothbrush"};
		
		int lvl[11];
		int sup[11];
		int sup1[11][11];
		int itm[10];
		int cnt;
		int n;
		int supr;
		void level();
		void valid();
		void display();
		void trans();
		void rules();
};
void aproiri::trans(){
	int i,j,k,l,tx,it=0;
	cout<<"\nEnter the number of transactions: ";
	cin>>cnt;
	tx=cnt;
	int tran[cnt][11];
	cout<<"\n"<<cnt;
	cout<<"\n.............................Available Items................................\n";
	cout<<"\n 1.Mango \n 2.Onion \n 3.Apple \n 4.Corn \n 5.Eggs \n 6.Chocolate \n 7.Nuts \n 8.Keychain \n 9.Knife \n 10.Jar \n 11.Toothbrush\n";
	for(i=0;i<tx;i++){
		for(k=0;k<11;k++){
			tran[i][k]=99;
		}
	}
	for(i=0;i<11;i++){
		for(k=0;k<11;k++){
			sup1[i][k]=0;
		}
	}
	for(i=0;i<11;i++){
		lvl[i]=0;
		sup[i]=0;
	}	
	for(i=0;i<tx;i++){
		cout<<"Enter the number of items(Atmost 5 items per transaction) for transaction: "<<i+1<<" : ";
		cin>>j;
		for(k=0;k<j;k++){
			cout<<"Enter the item number: "<<k+1<<" : ";
			cin>>it;
			tran[i][it-1]=1;
			lvl[it-1]=lvl[it-1]+1;		
		}
		
	}
	for(i=0;i<tx;i++){
		cout<<"T are................"<<i+1<<" : ";
		for(k=0;k<11;k++){
			cout<<tran[i][k]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n"<<cnt;
	cout<<"\n..................... TRANSACTIONS ARE ....................\n";
	for(i=0;i<tx;i++){
		cout<<"\nItems for transaction: "<<i+1<<": ";
		for(j=0;j<11;j++){
			if(tran[i][j]==1){
				cout<<ls[j]<<" ";
			}
		}
		cout<<"\n";
	}
	for(i=0;i<11;i++){
		cout<<"\n"<<ls[i]<<" : "<<lvl[i];
		if(lvl[i]>=2){
			sup[i]=lvl[i];
			
		}
		

	}
	cout<<"\n Transactions supported..............";
	for(i=0;i<11;i++){
		if(sup[i]>0){
				cout<<"\n"<<ls[i]<<" : "<<sup[i];
			}
	
	}
	cout<<"\n";
	for(i=0;i<11;i++){
		if(sup[i]>=2){
			for(j=i;j<11;j++){
				if(sup[j]>=2 && j!=i){
					for(l=0;l<tx;l++){
						if(tran[l][i]==tran[l][j]){
							sup1[i][j]=sup1[i][j]+1;
							
						}
					}
				}
			}
		}
	}
	cout<<"\n Level 2.................";
	cout<<"\n";
	for(i=0;i<11;i++){
		for(k=0;k<11;k++){
			if(sup1[i][k]>=2){
			
				cout<<ls[i]<<", "<<ls[k]<<": "<<sup1[i][k]<<"\n";
			
		}
		
	}
			
	}		
		
}			
int main(){
	aproiri app;
	app.trans();
	
	return 0;
}
