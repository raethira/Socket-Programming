
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
#define PORT 21849
using namespace std;
   
    int main()
                {
        int ssockdptr,valread;
        struct sockaddr_in server_addr;
            int childsocket;
           
        int addlen = sizeof(server_addr);
        char buffer[1000] = {0};
         const char *sendbuffer ="Hi this is server";
   
       if(!( ssockdptr = socket(AF_INET, SOCK_STREAM, 0))>0)
        {
        cout<<"error in socket"<<endl;
         }

               
            //memset(&serverAddr, '\0', sizeof(serverAddr));
          cout<<"Server is up and running"<<endl; 
               server_addr.sin_family = AF_INET;             
               server_addr.sin_port = htons(PORT);
               server_addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(ssockdptr, (struct sockaddr*)&server_addr,sizeof(server_addr) ) < 0)
               {
               cout<<"error in connection"<<endl;
               exit(1);
                }
         cout<<"hello"<<endl;
        if(listen(ssockdptr, 4)< 0)
           {
                cout<<"Error in listening";
               exit(1);
}
        if((childsocket = accept(ssockdptr, (struct sockaddr*)&server_addr, (socklen_t*)&addlen);  
        
        valread = read(childsocket, buffer, 1000);
                cout<<buffer;
        send(childsocket, sendbuffer, strlen(sendbuffer), 0);
                return 0;
                }


