#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>
#define PORT 26849
using namespace std;

int main()
{

int sock ;
int valread;
struct sockaddr_in serv_addr;
char buffer[5000];
int count =0;
int pos1=0;
int pos3=0;
int pos4=0;
int pos5=0;
int pos6 =0;
int pos7 =0;
int flag1 =0;
string buffer_1,func,buffer_2,word,meaning,word1,meaning1,buffer_3,flag,buffer_4,buffer_5;
//creating Tcp socket
if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
{
cout<<"Error, Socket went wrong"<<endl;
exit(1);
}
memset(&serv_addr,'0',sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_port =htons(PORT);
if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
{
cout<<"Invalid Address"<<endl;
exit(1);
}
if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
{
cout<<"No connection"<<endl;
exit(1);
}
cout<<"The Monitor is up and running"<<endl;
while(1)
{
//Recieving the result from Aws
valread=recv(sock,buffer,5000,0);
buffer[valread]='\0';
stringstream s1;
int temp= strlen(buffer);
for(int i=0;i<=temp;i++)
{
buffer_1 = buffer_1+buffer[i];
}
int pos=0;
pos = buffer_1.find('&');
func = buffer_1.substr(0,pos);
buffer_2 = buffer_1.substr(pos+1);
pos1 = buffer_2.find('$');
word = buffer_2.substr(0,pos1);
buffer_3 = buffer_2.substr(pos1+1);
if(func=="search")//For displaying Search operation results
{
meaning = buffer_3.substr(0,buffer_3.find('^'));
buffer_3.erase(0,buffer_3.find('^')+1);
pos3 = buffer_3.find(':');
word1 = buffer_3.substr(0,pos3);
cout<<"word1"<<word1<<">"<<endl;
buffer_3.erase(0,buffer_3.find(':')+1);
pos4 = buffer_3.find('>');
meaning1 = buffer_3.substr(0,pos4);
cout<<word1.length()<<endl;
if(meaning.length()!=0&&word1.length()!=1)
{
cout<<"Found a match for "<<"<"<<word<<">"<<":"<<endl;
cout<<"<"<<meaning<<">"<<endl;
cout<<"One edit distane match is "<<"<"<<word1<<">"<<":"<<endl;
cout<<"<"<<meaning1<<">"<<endl;
}
else if (meaning.length()==0&& word1.length()!=1)
{
cout<<"Found no matches for "<<"<"<<word<<">"<<endl;
cout<<"One edit distane match is "<<"<"<<word1<<">"<<":"<<endl;
cout<<"<"<<meaning1<<">"<<endl;
}
else if(meaning.length()!=0&&word1.length()==1)
{
cout<<"Found a match for "<<"<"<<word<<">"<<":"<<endl;
cout<<"<"<<meaning<<">"<<endl;
cout<<"Found no one edit distance match for "<<"<"<<word<<">"<<endl;
}
else if(meaning.length()==0&&word1.length()==0)
cout<<"Found no matches and no one edit distance match word for "<<"<"<<word<<">"<<endl;
}
if(func == "prefix")// For displaying Prefix operations results
{
pos5 = buffer_3.find('@');
flag = buffer_3.substr(pos5+1);
buffer_4 = buffer_3.substr(0,pos5);
s1<<flag;
s1>>flag1;
if(flag1!=0)
{
cout<<"Found "<<"<"<<flag<<">"<<" matches for "<<"<"<<word<<">"<<endl;
for(int i =0; i<flag1;i++)
{
pos6 = buffer_4.find("*");
buffer_5 = buffer_4.substr(pos7,pos6);
cout<<"<"<<buffer_5<<">"<<endl;
buffer_4 = buffer_4.substr(pos6+1);
pos6=0;
pos7=0;
}
}
else
cout<<"Found no matches for "<<"<"<<word<<">"<<endl;
}
//Resetting the variables
buffer_1.clear();
func.clear();
buffer_2.clear();
word.clear();
meaning.clear();
word1.clear();
meaning1.clear();
buffer_3.clear();
flag.clear();
buffer_4.clear();
buffer_5.clear();
s1.clear();
pos4=0;
pos5 =0;
pos3=0;
pos1=0;
pos6=0;
flag1 =0;
pos7 =0;
}
close(sock);
return 0;
}
