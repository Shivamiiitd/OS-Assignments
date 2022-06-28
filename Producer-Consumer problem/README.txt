It is a producer consumer problem. In producer, we open the /dev/urandom file using open system 
call in read only mode. After this we read 8 bytes of data from /dev/urandom from the read system 
call. We store these 8 bytes of data in a character array and then we pass it to writer system call 
defined in Kernel. In consumer, we create a character array. Now we call the reader system call 
defined in Kernel and then store the 8 bytes received from reader system call in that array. Now 
by a for loop, we print the random 8 bytes received from reader system call. Now in kernel, we first 
of all define two system calls reader and writer in syscall_64.tbl. Now in sys.c file first of all 
I have implemented a queue by array implemetation and defined two function enqueue and dequeue from 
adding and removing elemnts from the queue. Now in writer system call, there is parameter called 
data which would get enqueue in queue. I have used __copy_from_user function to get data from user 
space i.e. Producer to kernel. I have done the enqueue operation inside the reader-writer semaphore 
so that reader system call cannot access the queue while writer is writing something in the queue. 
Similarly in the reader system call, there is parameter called data which will be sent back to 
consumer. Here dequeue operation is performed and again it is performed in critical section. Now I 
sent data back to user space i.e. consumer by the __copy_to_user system call. Then the 8 bytes of data 
get printed in the Consumer. This process continues.

Commands for executing the code:
On 1st Terminal:
    make a
    ./a

On 2nd Terminal:
    make b
    ./b
(Makefile is attached)
