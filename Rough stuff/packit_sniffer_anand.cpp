#include <iostream>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fstream>

using namespace std;

int sock_raw;
int tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j;
struct sockaddr_in source,dest;

int main(void)
{
  void ProcessPacket(char *buffer,int data_size);
  void print_tcp_header(char * buffer,int data_size);
  void print_ip_header(char * buffer,int data_size);
  fstream  log_file;
  log_file.open("packet_sniff", ios::out | ios::in );
  cout<<"Starting capturing packets\n";
  sock_raw = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
  if(sock_raw < 0)
    {
      cout<<"Socket error \n";
    }
  struct sockaddr s_addr;
  struct in_addr in;
  char buffer[65536]; 
  while(1)
  {
    unsigned int s_addr_size = sizeof(s_addr);
    int data_size = recvfrom(sock_raw , buffer ,65536 , 0 , &s_addr , &s_addr_size);
    if(data_size < 0)
      {
	cout<<"Recv from error ,Failed to get packets \n";
	return 1;
      }
    ProcessPacket(buffer , data_size);
  }
  close(sock_raw);
  cout<<"Finished";
  return 0;
}
void ProcessPacket(char *buffer,int data_size)
{
  struct iphdr *ip_header = (struct iphdr*)buffer;
  ++total;
  switch (ip_header->protocol)
    {
    case 1: 
      ++icmp;
      break;
    case 2:
      ++igmp;
      break;
    case 6:
      ++tcp;
      print_tcp_packet(buffer , data_size);
      break;
    case 17:
      ++udp;
      break;
    default:
      ++others;
      break;
    }
  cout<<"Tcp : "<<tcp<<" Udp : "<<udp<<" Icmp : "<<icmp<<"\n";
}
void print_tcp_header(char *buffer,int data_size)
{
  unsigned short iphdrlen;
  struct iphdr *iph = (struct iphdr *)buffer;
  iphdrlen = iph->ihl*4;
  struct tcphdr *tcph = (struct tcphdr*)(buffer + iphdrlen);
  print_ip_header(buffer,size);
  
}
void print_ip_header(char * buffer,int data_size)
{
  unsigned short iphdrlen;
  struct iphdr *iph = (struct iphdr*)buffer;
  iphdrlen = iph->ihl*4;
  
}
//http://libtins.github.io/benchmark/
