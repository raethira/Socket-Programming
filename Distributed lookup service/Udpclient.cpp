#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define port 21344

using namespace std;
int main()
{

int sockfd;
struct sockaddr_in server_addr;
char buffer[2048];
socklen_t addr_size;

sockfd= socket(AF_INET,SOCK_DGRAM,0);
memset(&server_addr,'\0',sizeof(server_addr));
server_addr.sin_family=AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
strcpy(buffer,"Hello server");
sendto(sockfd,buffer,2048,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
cout<<buffer;

return 0;
}
