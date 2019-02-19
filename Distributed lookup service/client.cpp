#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#include<sstream>
#define PORT 25849


 using namespace std;
int main(int argc, char *argv[])
{
int sock=0;
int valread;
struct sockaddr_in serv_addr;
 char buff[5000] = {0};
char buffer[5000] = {0};
string func;
string word;
string buffer_1,buffer_2,buffer_3,buffer_4,buffer_5;
int temp1;
int pos1=0;
int pos2=0;
stringstream s1;
int flag=0;
int pos3 =0;
int pos4=0;

int count =0;
cout<<"The client is up and running"<<endl;
if(argc == 1) { 
        cout<<"ERROR: Expected atleast 1 argument"<<endl;
        return 0;
    }
    int size = 0;
    while(argv[size]) { 
        size++;
    }
    size--;
    if(size == 1) { 
        cout<<argv[1]<<endl;
        return 0;
    }
    int i;
    int v = strlen(argv[1]) + strlen(argv[2]); 

    char *str = (char *)malloc(v);
    strcat(str, argv[1]); 
    strcat(str, " ");
    strcat(str, argv[2]);
    strcat(str, " ");
    for(i = 3; i <= size; i++) {
        str = (char *)realloc(str, (v + strlen(argv[i]))); 
        strcat(str, argv[i]);
        strcat(str, " ");
    }
memset(buff,0,sizeof(buff));
//converting array of strings into character array
strcpy(buff,str);

for(int j = 0; j<6;j++)
{
func = func+buff[j];
}
int g = strlen(buff);
for(int k =7;k< g-1;k++)
{
word = word+buff[k];
}
cout<<"The client sent "<<"<"<<word<<">"<<" and "<<"<"<<func<<">"<<" to AWS "<<endl;

// creating the socket
if((sock= socket(AF_INET,SOCK_STREAM,0))<0)
{
cout<<"error, Socket went wrong"<<endl;
exit(1);
}
memset(&serv_addr,'0',sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
{
cout<<"Invalid address"<<endl;
exit(1);
}

if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
{
cout<<"No connection"<<endl;
exit(1);
}

send(sock,buff,strlen(buff),0);
valread = read(sock,buffer,5000);
temp1 = strlen(buffer);
for(int j=0;j<temp1;j++)
{
buffer_1 =buffer_1+buffer[j];
}
if(func=="search")//Displaying Results for search operation
{
pos1 = buffer_1.find("?");
buffer_2 = buffer_1.substr(0,pos1);
if(buffer_2.length()!=0)
cout<<"Found a match for "<<"<"<<word<<">"<<":"<<"<"<<buffer_2<<">"<<endl;
else
cout<<"Found no matches for "<<"<"<<word<<">"<<endl;
}
if (func=="prefix")//Displaying Results for prefix operations
{
pos2 = buffer_1.find("@");
buffer_3 = buffer_1.substr(0,pos2);
buffer_4 = buffer_1.substr(pos2+1);
s1<<buffer_4;
s1>>flag;
if(flag !=0)
{
cout<<"Found "<<"<"<<buffer_4<<">"<<" matches for "<<"<"<<word<<">"<<endl;
for(int i =0; i<flag;i++)
{
pos3 = buffer_3.find("*");
buffer_5 = buffer_3.substr(pos4,pos3);
cout<<"<"<<buffer_5<<">"<<endl;
buffer_3 = buffer_3.substr(pos3+1);
pos3=0;
pos4=0;
}
}
else
cout<<"Found no matches for "<<"<"<<word<<">"<<endl;
}
return 0;
}

