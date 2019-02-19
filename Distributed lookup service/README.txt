- Implementation:
A simplified version of lookup services was implemented. Three backend servers were created that have UDP connetions to another server named AWS which inturn is connected to a client and monitor through TCP connetions. Two major database operations of search and prefix were performed on the distributed database consisting of words in english language and their meanings.The backend servers contained distributed databse while the computation was performed by AWS server and the respective results were displayed on both client and monitor.

- List of code files:
1) ServerA.cpp : This file performs the database operations of search and prefix on backend file dict_A.txt and the respective rsults were sent to Aws.
2)ServerB.cpp : This file performs the database operations of search and prefix on backend file dict_B.txt and the respective rsults were sent to Aws.
3)ServerC.cpp : This file performs the database operations of search and prefix on backend file dict_C.txt and the respective rsults were sent to Aws.
4)Aws.cpp: The Aws sends combined results from the backend servers to both client and monitor.If the required funcion is search , then word along with defination is sent to client and monitor recieves one edit distane match ,its meaning and original match.
5) client.cpp: The client displays the resuts of the database operations as recieved from Aws.If the function is Search,it displays meaning of the word and if the function is prefix it displays  all the words with that prefix from all the backend servers. 
6)monitor.cpp: If the database function is search , monitor displays the original meaning and also one edit distance  match along with its meaning.If the function is Prefix , it displays all the words with that prefix from all the backend servers.

- Format of the messages sent: The messages displayed on all the servers along with client and monitor are of the format specified in the problem statement. 

- Idiosyncrasy: The project is case sensitive i.e the user needs to enter the function in all lowercase characters and the word with first character being uppercase followed by all lowercase characters.
'word

- Reused code: Reffered to youtube videos by IdiotDeveloper and Shriram Vasudevan for setting up Tcp and Udp sockets. 

