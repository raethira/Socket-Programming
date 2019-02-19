
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#define port 21849
using namespace std;

int main()
{
int csockdptr=0;
char buffer[1024] = {0};
int l,valread;
struct sockaddr_in address;
 const char *funclient = "i am client";
if (csockdptr = socket(AF_INET, SOCK_STREAM, 0) < 0)
{
cout<<"error in socket formation"<<endl;
exit(1);
}
else
cout<<"Client socket created successfully"<<endl;


memset(&address, '0',sizeof(address));
address.sin_family = AF_INET;
address.sin_port = htons(port);
address.sin_addr.s_addr = INADDR_ANY;
if(inet_pton(AF_INET,"127.0.0.1",&address.sin_addr)<=0)
{
cout<<"Invalid address"<<endl;
exit(1);
}

if((connect(csockdptr,(struct sockaddr*)&address, sizeof(address)) < 0))
{
cout<<"error in connection"<<endl;
exit(1);
}
else
cout<<"client to server TCP connection is successfull"<<endl;
l = strlen(funclient);
send(csockdptr, funclient, l,0);
valread = read(csockdptr, &buffer,strlen(buffer));
cout<<"The data sent by the server is "<<buffer<<endl;

cout<<"client socket got closed"<<endl;
return 0;
}
