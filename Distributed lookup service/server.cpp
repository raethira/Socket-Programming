#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define PORT 21894
#define port 21849


using namespace std;
int main()
{

int sock_fd,new_socket,valread;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer1[2048] = {0};
const char *h = "Hello client";
int sockfd;
struct sockaddr_in server_addr;
char buffer2[2048];
socklen_t addr_size;
cout<<"The AWS is up and running"<<endl;

// creating a descriptor for server
if(!(sock_fd = socket(AF_INET,SOCK_STREAM,0))>0)
{
cout<<" error, SOCKET is wrong"<<endl;
exit(1);
}
//creating descriptor for client 
sockfd= socket(AF_INET,SOCK_DGRAM,0);
memset(&server_addr,'\0',sizeof(server_addr));

address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
server_addr.sin_family=AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


// Binding the socket

if(bind(sock_fd,(struct sockaddr*)&address,sizeof(address))<0)
{
cout<<"Error, Binding went wrong"<<endl;
exit(1);
}

// Listen 

if(listen(sock_fd,4)<0)
{
cout<<" erorr, Listening went wrong"<<endl;
exit(1);
}

//Accept

if((new_socket = accept(sock_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
{
cout<<" error, Accept went wrong "<<endl;
exit(1);
}
valread = read(new_socket,buffer1,2048);
cout<<buffer1<<endl;
send(new_socket,h,strlen(h),0);
strcpy(buffer2,"Hello server");
sendto(sockfd,buffer1,2048,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
cout<<buffer2<<endl;
return 0;
}


