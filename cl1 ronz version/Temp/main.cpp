#include<iostream>
#include<string>
char q[10][4]={};
char op[10][4]={};
int nodes;
int opc=0;
int subscnt=0;
int itrcnt=0;
using namespace std;
char dag(char tup[4])
{
    for(int i=0;i<itrcnt;i++)
    {
        if(tup[0]==q[i][0]&&tup[1]==q[i][1]&&tup[2]==q[i][2])
            return q[i][3];
    }
        return ' ';
}
void disp()
{
    cout<<"op\targ1\arg2\tres"<<endl;
    for(int i=0;i<opc;i++)
    {
        cout<<op[i][0]<<"\t"<<op[i][1]<<"\t"<<op[i][2]<<"\t"<<op[i][3]<<endl;
    }
}
int main()
{
    char subs[10][2]={};
    cout<<"enter the no. of nodes";
    cin>> nodes;
    cout<<"enter quadruple(op,ag1,ag2,res)";
    for(int i=0;i<nodes;i++)
    {
        int flag=0;
        cout<<"quadruple "<<i<<endl;
        cin>>q[i][0]>>q[i][1]>>q[i][2]>>q[i][3];
        for(int j=0;j<subscnt;j++)
        {
            if(subs[j][1]==q[i][1])
                q[i][1]= subs[j][0];
            if(subs[j][1]==q[i][2])
                q[i][2]= subs[j][0];
        }
        if(i!=0)
        {
            itrcnt=i;
            char ch = dag(q[i]);
            if(ch!=' ')
            {
                subs[subscnt][0]=ch;
                subs[subscnt][1]=q[i][3];
                subscnt++;
                flag =1;
            }
        }
        if(flag==0)
        {
            op[opc][0]=q[i][0];
            op[opc][1]=q[i][1];
            op[opc][2]=q[i][2];
            op[opc++][3]=q[i][3];
        }
    }
    disp();
return 0;
}
