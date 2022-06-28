In this part, we are using Sockets for Inter Process Communication between two processes. 
Here we have two files P1_sockets.c and P2_sockets.c. Here P1_sockets.c is the Client and 
P2_sockets.c is the server in the Unix Domain Sockets. In sockets we need to define a socket 
name so that client and server get connected by using that name. In sockets-server there are 
several stages. Creation of socket, binding, listen, accept, read and write and then close. 
Similarly in sockets-client there are creation of socket, connect, read and write and then 
close. Accept is a blocking system call in server, that is code will not execute further 
after accept, till any client does not get connected to the server. And obviously connect in 
client helps in connecting client to the server. Now in Client that is in P1_sockets.c we 
defined a function randstr() which when called generates a array of 50 random strings. Then 
we have some syntax and defined a socket by AF_UNIX and SOCK_STREAM data. Then we use the 
connect and then defined two arrays, one character array and one string array for storing 
the strings and indexes respectively. Then by using for and loops and write system call, 
we send the data to the server that is to P2_sockets.c. Now in server we defined the socket, 
bind, listen, accept. Now after client get connected, we read the strings and indexes that 
are coming from client and then we find the highest ID among those 5 indexes and then send 
it back to client. Then client receives that highest ID from server and print it on the 
terminal. Then we close the socket.

For Compiling and executing the programs using a Makefile is:
Follow these intructions:
We need two terminals
On Teminal 1:
    make f
    ./f
Then On Terminal 2:
    make e
    ./e