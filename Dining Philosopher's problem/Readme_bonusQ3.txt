There are 5 philosophers on a round table, and every philosopher has a plate and one fork each on his left 
hand side and right hand side. Also now there are 4 bowls on the centre of the table. I am creating 5 threads 
one for each philosophers in the main function. In this problem maximum 2 philosophers can eat at a time. 
So I have created a semaphore array of size 5 and a semaphore mutex variable. Also here I have defined an integer 
named bowls which is initialised to 4. Whenever a philosopher needs to take forks to eat, mutex variable decrements 
so that he can enter into the critical section and no other philosopher can enter it. Now philosopher checks 
whether his left and right philosophers are eating or not and there is atleast one bowl on the table. If they 
are not eating and there is atleast one bowl then philosopher can eat, and if they are eating or no bowl is on 
the table then philosopher have to wait. Now here the mutex variable again increments to get out of the critical 
section. After taking forks and a bowl, value of bowl is decremented by 1, philosopher eat the food and then he 
put back the forks and bowl again by going to the critical section by decrementing mutex variable. Here now bowls 
value is incremented by 1. This process continues, like when one philosopher is eating his left and right 
neighbours can't eat, but when he finished eating then the neighbours can eat.

Commands for executing the code:
On Terminal:
    make c
    ./c
(Makefile is attached)