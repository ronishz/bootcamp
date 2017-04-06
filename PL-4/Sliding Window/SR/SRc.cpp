//CLIENT SIDE
//SELECTIVE_REPEAT
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<iostream>

using namespace std;

int main()
{
        int sfd,lfd,len,choice;
        char str[20],str1[20],err[20];
        struct sockaddr_in saddr,caddr;

        sfd=socket(AF_INET,SOCK_STREAM,0);

        if(sfd<0)
                perror("FdError");

        bzero(&saddr,sizeof(saddr));
        saddr.sin_family=AF_INET;
        saddr.sin_addr.s_addr=INADDR_ANY/*inet_addr("172.16.132.104")*/;
        saddr.sin_port=htons(546);

        connect(sfd,(struct sockaddr*)&saddr,sizeof(saddr));

        for(;;)
        {
                read(sfd,str,20);
                if(!strcmp(str,"exit"))
                {
                        cout<<"Exiting..\n";
                        break;
                }
                cout<<"\n\nReceived:"<<str<<"\n\n1.Do u want to report an error(1-Yes 0-No): ";
                cin>>choice;

                if(!choice)
                        write(sfd,"-1",sizeof("-1"));
                else
                {
                        cout<<"Enter the sequence no of the frame where error has occured: \n";
                        cin>>err;
                        write(sfd,err,sizeof(err));
                        read(sfd,str,20);
                        cout<<"\n\nReceived the re-transmitted frames: "<<str<<"\n\n";
                }
        }
}

