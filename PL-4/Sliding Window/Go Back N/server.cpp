//SERVER SIDE
//GO BACK N
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<iostream>
#include<unistd.h>
#define SIZE 4

using namespace std;

int main()
{
        int sfd,lfd,len,i,j,status;
        char str[20],frame[20],temp[20],ack[20];
        struct sockaddr_in saddr,caddr;

        sfd=socket(AF_INET,SOCK_STREAM,0);

        if(sfd<0)
                perror("Error");

        bzero(&saddr,sizeof(saddr));
        saddr.sin_family=AF_INET;
        saddr.sin_addr.s_addr=htonl(INADDR_ANY);
        saddr.sin_port=htons(6666);
        if(bind(sfd,(struct sockaddr*)&saddr,sizeof(saddr))<0)
                perror("Bind Error");

        listen(sfd,5);
        len=sizeof(&caddr);
        lfd=accept(sfd,(struct sockaddr*)&caddr,(socklen_t *)&len);

        cout<<" Enter the text : \n";
        cin>>str;

        cout<<str;

        i=0;
        while(i<strlen(str))
        {
                memset(frame,0,20);
                strncpy(frame,str+i,SIZE);
                cout<<" \n Transmitting Frames. ";
                len=strlen(frame);

                cout<<"\n";

                write(lfd,frame,sizeof(frame));
                read(lfd,ack,20);

                sscanf(ack,"%d ",&status);

                if(status==-1)
                        cout<<" Transmission is successful. \n";
                else
                {
                        cout<<" Received error in "<<status<<"\n\n";
                        cout<<"\n\n Retransmitting Frame. ";
                        for(j=0;;)
                        {
                                frame[j]=str[j+status];
                                cout<<j+status;
                                j++;
                            if((j+status)%4==0)
                                        break;
                        }
                        cout<<"\n";
                        frame[j]='\0';
                        len=strlen(frame);
                   
                        write(lfd,frame,sizeof(frame));
                }
                i+=SIZE;
        }
        write(lfd,"exit",sizeof("exit"));
        cout<<"Exiting...\n";
        sleep(2);
        close(lfd);
        close(sfd);
}



