#include<iostream>
#include<sstream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<fstream>
#define port 21849
#define port1 24849

using namespace std;
int main()
{

int sockfd,len,len1;
struct sockaddr_in si_me,si_other;
char buffer[1024];
socklen_t  addr_size;
//creating the UDP socket
sockfd = socket(AF_INET,SOCK_DGRAM,0);
memset(&si_me,'\0',sizeof(si_me));
si_me.sin_family = AF_INET;
si_me.sin_port=htons(port);
si_me.sin_addr.s_addr=INADDR_ANY;
si_other.sin_family =AF_INET;
si_other.sin_addr.s_addr = INADDR_ANY;
string word;
string t,term,res;
string res2;
int pos,pos1;
socklen_t size;
string func;
int n=0;
char result[5000];
char str2Char_array[5000];
char str1Char_array[5000];
string req_str ="";
string res1;
int count =0;
int count2=0;
string str;

//Binding the socket
if((bind(sockfd,(struct sockaddr*)&si_me,sizeof(si_me))) < 0)
{
cout<<"Failed to bind"<<endl;
}
addr_size = sizeof(si_other);
cout<<"The ServerA is up and running using UDP on port "<<"<"<<port<<">"<<endl; 
while(true)
{
recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&si_other,&addr_size);

for(int j = 0; j<6;j++)
{
func = func+buffer[j];
}

int g = strlen(buffer);
for(int k =7;k< g-1;k++)
{
word = word+buffer[k];
}
stringstream ss;

cout<<"The ServerA recieved input "<<"<"<<word<<">"<<" and operation "<<"<"<<func<<">"<<endl;
if (func =="search")//Search operation code piece 
{
len = word.size();
ifstream infile;
strcpy(str1Char_array,word.c_str());
infile.open("/home/ee450/Downloads/backendA.txt");
while(getline(infile,t))
{
pos = t.find(":");
term =t.substr(0,pos-1);
len1 = term.size();
strcpy(str2Char_array,term.c_str());
int count1 =0;
if(len==len1)
{
for(int j = 0;j<len;j++)
{
if(str1Char_array[j]!=str2Char_array[j])
{
count1++;

}
}
if(count1==1)
{
req_str = term;
count++;
res1 = t.substr(pos+3);
}
}
if(!term.compare(word))
{
res=t.substr(pos+3);
count2++;
}
}
if(count2==0)
count2=0;
else 
count2 = 1;
cout<<"The ServerA has found "<<"<"<<count2<<">"<<" match and "<<"<"<<count<<">"<<" similar words"<<endl;

res2 = res+"<"+req_str+":"+res1+">";
}

else if(func=="prefix")//Prefix operation code piece
{
ifstream infile;
infile.open("/home/ee450/Downloads/backendA.txt");
while(getline(infile,t))
{
pos = t.find(":");
term =t.substr(0,pos-1);

pos1 = term.find(word);
if(pos1 == 0)
{
 n=n+1;
res.append(term);
res.append(" *");
}
}
ss << n;
str = ss.str();
res2 = res+"@"+str;
cout<<"The ServerA has found" <<"<"<<n<<">"<<" matches"<<endl;
}
//converting result to character array
int temp = res2.size();
for(int a=0;a<=temp;a++)
{
result[a] = res2[a];
}
//Snding the result to Aws 
sendto(sockfd,result,2048,0,(struct sockaddr*)&si_other,addr_size);
cout<<"The ServerA finished sending the output to AWS "<<endl;
//Resetting all the variables 
memset(buffer,0,sizeof(buffer));
memset(result,0,sizeof(result));
g=0;
func.clear();
word.clear();
len =0;
memset(str2Char_array,0,sizeof(str2Char_array));
memset(str1Char_array,0,sizeof(str1Char_array));
len1 =0;
count =0;
pos=0;
term.clear();
req_str.clear();
res1.clear();
res.clear();
str.clear();
pos1=0;
n=0;
temp=0;
count2 =0;
res2.clear();

}
close(sockfd);
return 0;
}



