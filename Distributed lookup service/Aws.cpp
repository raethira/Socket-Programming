#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>
#define PORT 25849
#define port 24849
#define port1 21849
#define port2 22849
#define port3 23849
#define port4 26849


using namespace std;
int main()
{
int sock_fd1,new_socket1,valread1,val;
struct sockaddr_in address1;
socklen_t addrlen1 = sizeof(address1);
char buffer_m[5000];

int sock_fd,new_socket,valread;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer1[5000] = {0};
int sockfd;
struct sockaddr_in server_addr,server_addr1,server_addr2,server_addr3;
struct sockaddr_in server_addr4,server_addr5,server_addr6;
char buffer2[5000];
socklen_t addr_size;
socklen_t add_size1;
socklen_t add_size2;
socklen_t add_size3;
char buffer3[5000];
char buffer4[5000];
char buffer5[5000];
char result_2[5000];
string func;
string word;
int buffsize = 5000;
string buffer_3,buffer_4,buffer_5;
string res1;
char res2[5000];
int count =0;
string r1,r2,r3;
int count3=0;
int count4=0;
int count5=0;
int count6=0;
int flag1=0;
int flag2 =0;
int flag3 =0;
int flag4 =0;
string match_1,match_2,match_3,match_4,str;
int count7 =0;
int count8 =0;
int count9 =0;
int temp1=0;
string buffer_31,buffer_41,buffer_51,res3;
cout<<"The AWS is up and running"<<endl;
//Creating Tcp socket for client 
if(!(sock_fd = socket(AF_INET,SOCK_STREAM,0))>0)
{
cout<<" error, SOCKET is wrong"<<endl;
exit(1);
}
//creating Tcp socket for monitor
if(!(sock_fd1 = socket(AF_INET,SOCK_STREAM,0))>0)
{
cout<<"error,SOCKET is Wrong"<<endl;
exit(1);
}

sockfd= socket(AF_INET,SOCK_DGRAM,0);
memset(&server_addr,'\0',sizeof(server_addr));

address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
server_addr.sin_family=AF_INET;
server_addr.sin_port = htons(port);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
server_addr1.sin_family = AF_INET;
server_addr1.sin_port = htons(port1);
server_addr2.sin_family =AF_INET;
server_addr2.sin_port =htons(port2);
server_addr3.sin_family =AF_INET;
server_addr3.sin_port = htons(port3);

server_addr4.sin_family = AF_INET;
server_addr4.sin_port = htons(port1);
server_addr5.sin_family =AF_INET;
server_addr5.sin_port =htons(port2);
server_addr6.sin_family =AF_INET;
server_addr6.sin_port = htons(port3);

address1.sin_family = AF_INET;
address1.sin_addr.s_addr = INADDR_ANY;
address1.sin_port = htons(port4);


// Binding the socket 

if(bind(sock_fd,(struct sockaddr*)&address,sizeof(address))<0)
{
cout<<"Error, Binding went wrong"<<endl;
exit(1);
}
//Binding the socket
if(bind(sock_fd1,(struct sockaddr*)&address1,sizeof(address1))<0)
{
cout<<"Error ,Binding went wrong"<<endl;
exit(1);
}
if((bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)))<0)
{
cout<<"Failed to bind"<<endl;
}
//listening to monitor
if(listen(sock_fd1,4)<0)
{
cout<<"Error,Binding went wrong"<<endl;
exit(1);
}
//listening to client
if(listen(sock_fd,4)<0)
{
cout<<" erorr, Listening went wrong"<<endl;
exit(1);
}
//Child socket to accept from monitor
if((new_socket1=accept(sock_fd1,(struct sockaddr*)&address1,&addrlen1))<0)
{
cout<<"Error,ACCEPT wemt wrong"<<endl;
exit(1);
}

while(true)
{
//child socet to accept from client
if((new_socket = accept(sock_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0)
{
cout<<" error, Accept went wrong "<<endl;
exit(1);
}
valread = read(new_socket,buffer1,2048);
for(int j = 0; j<6;j++)
{
func = func+buffer1[j];
}

int g = strlen(buffer1);
for(int k =7;k< g-1;k++)
{
word = word+buffer1[k];
}
stringstream s1;
stringstream s2;
stringstream s3;
stringstream ss;
//Sending the word and function to all the three backend servers
cout<<"The AWS recieved input= "<<"<"<<word<<">"<<" and function= "<<"<"<<func<<">"<<" from the client using TCP over port "<<"<"<<PORT<<">"<<endl;
sendto(sockfd,buffer1,5000,0,(struct sockaddr*)&server_addr1,sizeof(server_addr1));
cout<<"The AWS sent "<<"<"<<word<<">"<<" and function "<<"<"<<func<<">"<<" to Backend-Server A"<<endl;
sendto(sockfd,buffer1,5000,0,(struct sockaddr*)&server_addr2,sizeof(server_addr2));
cout<<"The AWS sent "<<"<"<<word<<">"<<" and function "<<"<"<<func<<">"<<" to Backend-Server B"<<endl;
sendto(sockfd,buffer1,5000,0,(struct sockaddr*)&server_addr3,sizeof(server_addr3));
cout<<"The AWS sent "<<"<"<<word<<">"<<" and function "<<"<"<<func<<">"<<" to Backend-Server C"<<endl;
add_size1 = sizeof(server_addr4);
add_size2 =sizeof(server_addr5);
add_size3 =sizeof(server_addr6);
//Recieving the result from all the three backend servers
recvfrom(sockfd,buffer3,5000,0,(struct sockaddr*)&server_addr4,&add_size1);
if(ntohs(server_addr4.sin_port)==21849){
buffer_3 = string(buffer3);
}
else if(ntohs(server_addr4.sin_port) ==22849){
buffer_4 = string(buffer3);
}
else {
buffer_5 = string(buffer3);
}
recvfrom(sockfd,buffer4,5000,0,(struct sockaddr*)&server_addr5,&add_size2);
if(ntohs(server_addr5.sin_port)==21849){
buffer_3 = string(buffer4);
}
else if(ntohs(server_addr5.sin_port)==22849) {
buffer_4 = string(buffer4);
}
else{
buffer_5 = string(buffer4);
}
recvfrom(sockfd,buffer5,5000,0,(struct sockaddr*)&server_addr6,&add_size3);
if(ntohs(server_addr6.sin_port) == 21849){
buffer_3 = string(buffer5);
}
else if(ntohs(server_addr6.sin_port) == 22849){
buffer_4 = string(buffer5);
}
else{
buffer_5 = string(buffer5);
}
int pos1=0;
int pos2=0;
int pos3=0;
int pos4=0;
int pos5=0;
int pos6=0;
string meaning1,match1,meaning2,match2,meaning3,match3,meaning,match;
//Combining the results for search and prefix operations 
if (func =="search")
{
pos1 = buffer_3.find('<');
meaning1 = buffer_3.substr(0,pos1);
match1 = buffer_3.substr(pos1+1,(buffer_3.find('>')));
if(match1[0] ==':')
match1.clear();
pos2 = buffer_4.find('<');
meaning2 = buffer_4.substr(0,pos2);
match2 = buffer_4.substr(pos2+1,(buffer_4.find('>')));
if(match2[0] ==':')
match2.clear();
pos3= buffer_5.find('<');
meaning3 = buffer_5.substr(0,pos3);
match3 = buffer_5.substr(pos3+1,(buffer_5.find('>')));
if(match3[0] ==':')
match3.clear();
if((meaning1.length())!=0)
meaning = meaning1;
if(match1!="")
match = match1;
if((meaning.length())==0)
{
if((meaning2.length())!=0)
meaning = meaning2;
else if((meaning3.length())!=0)
meaning = meaning3;
}
if(match1=="")
{
if(match2!="")
{
match = match2;
}
else if (match3!="")
match = match3;
}
int pos7=0;
int pos8=0;
int pos9=0;
int pos10=0;
int pos11 =0;
int pos12 =0;
int pos13 =0;
int pos14 =0;
pos7 = match.find("<");
pos8 = match.find(":");
match_1 = match.substr(pos7+1,pos8);
pos9 = match1.find("<");
pos10 = match1.find(":");
match_2 = match1.substr(pos9+1,pos10);
pos11 = match2.find("<");
pos12 = match2.find(":");
match_3 = match2.substr(pos11+1, pos12);
pos13 = match3.find("<");
pos14 = match3.find(":");
match_4 = match3.substr(pos13+1,pos14);
if(match_2.length()==0)
count7 =0;
else
count7 =1;
if(match_3.length()==0)
count8 =0;
else
count8 =1;
if(match_4.length()==0)
count9 =0;
else
count9 =1;

cout<<"The AWS recieved "<<"<"<<count7<<">"<<" similar words from Backend-Server <A> using UDP over port "<<"<"<<port1<<">"<<endl;
cout<<"The AWS recieved "<<"<"<<count8<<">"<<" similar words from Backend-Server <B> using UDP over port "<<"<"<<port2<<">"<<endl;
cout<<"The AWS recieved "<<"<"<<count9<<">"<<" similar words from Backend-Server <C> using UDP over port "<<"<"<<port3<<">"<<endl;
res1 = meaning+"?"+match+"$";
res3 = func+"&"+word+"$"+meaning+"^"+match;
 temp1 = res3.size();
for(int j=0;j<=temp1;j++)
{
result_2[j]= res3[j];
}
}
else
{
res1 = buffer_3+buffer_4+buffer_5;
pos4 = buffer_3.find("@");
r1 = buffer_3.substr(pos4+1);
buffer_31 = buffer_3.substr(0,pos4);
s1<<r1;
s1>>flag1;
pos5 = buffer_4.find("@");
r2 = buffer_4.substr(pos5+1);
buffer_41=buffer_4.substr(0,pos5);
s2<<r2;
s2>>flag2;
pos6 = buffer_5.find("@");
r3 = buffer_5.substr(pos6+1);
buffer_51 = buffer_5.substr(0,pos6);
s3<<r3;
s3>>flag3;
flag4 = flag1+flag2+flag3;
cout<<"The AWS recieved "<<"<"<<r1<<">"<<" matches from Backend-Server <A> using UDP over port "<<"<"<<port1<<">"<<endl;
cout<<"The AWS recieved "<<"<"<<r2<<">"<<" matches from Backend-Server <B> using UDP over port "<<"<"<<port2<<">"<<endl;
cout<<"The AWS recieved "<<"<"<<r3<<">"<<" matches from Backend-Server <C> using UDP over port "<<"<"<<port3<<">"<<endl;
cout<<"The AWS sent "<<"<"<<flag4<<">"<<" matches to client"<<endl;
cout<<"The AWS sent "<<"<"<<flag4<<">"<<" matches to the monitor via TCP port "<<"<"<<port4<<">"<<" for prefix"<<endl;
ss<<flag4;
str= ss.str();
res1 = buffer_31+buffer_41+buffer_51+"@"+str;
res3 = func+"&"+word+"$"+buffer_31+buffer_41+buffer_51+"@"+str;
temp1 = res3.size();
for(int j=0;j<=temp1;j++)
{
result_2[j]= res3[j];
}
}
int temp = res1.size();
for(int i = 0;i<=temp;i++)
{
res2[i] = res1[i];
}
if(func=="search")
{
if(meaning1.length()!=0)
count3 =1;
else 
count3 = 0;
if(meaning2.length()!=0)
count4 = 1;
else
count4 =0;
if(meaning3.length()!=0)
count5 = 1;
else
count5 = 0;
if(count3==0&&count4==0&&count5==0)
count6 =0;
else if(count3==1&&count4==0&&count5==0)
count6 =1;
else if(count3==0&&count4==1&&count5==0)
count6 =1;
else if(count3==0&&count4==0&&count5==1)
count6 =1;
else if(count3==0&&count4==1&&count5==1)
count6 = 1;
else if(count3==1&&count4==0&&count5==1)
count6 =1;
else if(count3==1&&count4==1&&count5==0)
count6 =1;
else if(count3==1&&count4==1&&count5==1)
count6 =1;
cout<<"The AWS sent "<<"<"<<count6<<">"<<" matches to client"<<endl;
if(match_1.length()!=0 && meaning.length()!=0)
{
cout<<"The AWS sent "<<"<"<<word<<">"<<" and "<<"<"<<match_1<<">"<<" to the monitor via TCP port "<<"<"<<port4<<">"<<" for search"<<endl;
}
else if(match_1.length()==0&& meaning.length()!=0){
cout<<"The AWS sent "<<"<"<<word<<">"<<" to the monitor via TCP port "<<"<"<<port4<<">"<<" for search"<<endl;
}
else if(match_1.length()!=0&&meaning.length()==0)
{
cout<<"The AWS sent "<<"<"<<match_1<<">"<<" to the monitor via TCP port "<<"<"<<port4<<">"<<" for search"<<endl;
}
}
// Sending the results to both client and monitor
int sent = send(new_socket,res2,strlen(res2),0);
val=send(new_socket1,result_2,strlen(result_2),0);
//Resetting the variables
memset(buffer1,0, sizeof(buffer1));
memset(buffer3,0, sizeof(buffer3));
memset(buffer4,0, sizeof(buffer4));
memset(buffer5,0, sizeof(buffer5));
memset(res2,0,sizeof(res2));
memset(result_2,0,sizeof(result_2));
res1.clear();
func.clear();
word.clear();
val=0;
buffer_3.clear();
buffer_4.clear();
buffer_5.clear();
temp=0;
count=0;
count3=0;
count4=0;
count5=0;
count6=0;
flag1 =0;
flag2 =0;
flag3 =0;
flag4=0;
count7 =0;
count8 =0;
count9=0;
temp1=0;
buffsize = 4000;
meaning1.clear();
meaning2.clear();
meaning3.clear();
match1.clear();
match2.clear();
match3.clear();
meaning.clear();
match.clear();
r1.clear();
r2.clear();
r3.clear();
str.clear();
res3.clear();
s1.clear();
s2.clear();
s3.clear();
buffer_31.clear();
buffer_41.clear();
buffer_51.clear();
match_1.clear();
match_2.clear();
match_3.clear();
match_4.clear();
}
close(sockfd);
close(sock_fd);
close(new_socket);
close(sock_fd1);
close(new_socket1);
return 0;
}

