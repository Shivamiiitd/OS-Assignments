In this part, we are using Message queues for Inter-Process Communication between two processes. 
Here we have two files P1_msgq.c and P2_msgq.c. In P1_msgq.c I have defind a function randstr() 
which when called will generate an array of 50 random strings. Now, in every message that we pass 
in message queue, there are two things, one is the main data(text) that is to be passed and another 
one is a long integer value, defining the message type. Now in P1_msgq.c, we created a new queue
using msgget() system call and assign a key value (Here 10) to it. Generally any message type value 
is 1. Then we defined two arrays, one is character array and another one is integer array and these 
arrays are storing strings and integers values of indexes that are to be passed to P2_msgq.c 
respectively. Now by using for loops and by coping the value of each string at each iteration of 
the for loop to the message data array we are passing the string to the message queue, i.e. the 
data of every message. Then we pass this whole message, using msgsnd() system call. By this msgsnd() 
system call, we pass our message to another process. Now in P2_msgq.c, we are opening the message 
queue using the msgget() system call, by the key (10) and then we are receiving the message that was 
sent by the P1_msgq.c by msgrcv() system call. msgrcv is basically "message receive" system call and 
by this we receive the message and then prints it on the terminal. Similarly we prints the indexes 
as well. Now we open a new message queue with key value 11 in P2_msgq.c for passing the highest ID 
to P1_msgq.c through this message queue. Now we find the highest ID of indexes and pass that ID to 
the secobd message queue similarly as previous one by the msgsnd() system call and then P1_msgq.c 
we receive the highest ID by msgrcv() system call and then prints it on the terminal.

For Compiling and executing the programs using a Makefile is:
Follow these intructions:
We need two terminals
On Teminal 1:
    make c
    make d
    ./d
Then On Terminal 2:
    ./c