In this part, we are using FIFO for Inter-Process Communication. Here we have two files 
P1_fifo.c and P2_fifo.c as per according to the question. In P1_fifo.c there is a function
randstr() which when called, generates an array of 50 random strings. FIFO pipes are created
by mkfifo system call and I have created two fifo pipes here. I have given both read and 
write permission to both the fifo. In P1_fifo.c first fifo pipe is opened in Write only mode. 
Next we have created two arrays, one character array and second one integer array, in which our 
string and indexes are stored respectively. Then by using for loops and write system call, we have 
written the data that we want to send to P2_fifo.c. Now in P2_fifo.c we have opened the first 
fifo pipe in Read only mode, where we are reading the data coming from P1_fifo.c by read system 
call and storing that data into the buffer. Next we are printing the strings and indexes in 
P2_fifo.c and we are finding the highest ID from those indexes. Now we opened the second fifo 
pipe in P2_fifo.c in write only mode, where we are writing the highest ID to P1_fifo.c. 
Similarly, in P1_fifo.c we are opening the second fifo pipe in read only mode, where we read 
the highest ID and then prints it. Now we are just closing both the fifo pipe file descriptors.

For Compiling and executing the programs using a Makefile is:
Follow these intructions:
We need two terminals
On Teminal 1:
    make a
    make b
    ./b
Then On Terminal 2:
    ./a