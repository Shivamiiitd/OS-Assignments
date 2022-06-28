#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

char status[5] = {'S','S','S','S','S'};
int philos[5] = {1, 2, 3, 4, 5};
 
sem_t mutex;
sem_t forks[5];
int bowls = 4;

void eat(int num)
{
	printf("Philosopher %d is Eating\n", num);
}

void finish(int num)
{
	printf("Philosopher %d has finished Eating\n", num);
}

void hungry(int num)
{
	printf("Philosopher %d is hungry\n", num);
}

void bowl(int num)
{
	printf("Philosopher %d has got a bowl\n", num);
}

void check(int num)
{
	if(num == 1)
	{
		if(status[0] == 'H' && status[1] != 'E' && status[4] != 'E' && bowls > 0)
		{
			status[0] = 'E';
			bowls--;
			bowl(1);
			eat(1);
			sleep(2);
			sem_post(&forks[0]);
		}
	}
	else if(num == 4)
	{
		if(status[3] == 'H' && status[4] != 'E' && status[2] != 'E' && bowls > 0)
		{
			status[3] = 'E';
			bowls--;
			bowl(4);
			eat(4);
			sleep(2);
			sem_post(&forks[3]);
		}
	}
	else
	{
		if(status[num-1] == 'H' && status[((num+1)%5) - 1] != 'E' && status[((num+4)%5) - 1] != 'E' && bowls > 0)
		{
			status[num-1] = 'E';
			bowls--;
			bowl(num);
			eat(num);
			sleep(2);
			sem_post(&forks[num-1]);
		}
	}
}

void taking_forks(int num)
{
	sem_wait(&mutex);
	status[num-1] = 'H';
	hungry(num);
	check(num);
	sem_post(&mutex);
	sem_wait(&forks[num-1]);
	sleep(1);
}

void putting_forks(int num)
{
	sem_wait(&mutex);
	status[num-1] = 'S';
	finish(num);
	bowls++;
	if(num == 1)
	{
		check(2);
		check(5);
	}
	else if(num == 4)
	{
		check(3);
		check(5);
	}
	else
	{
		check((num+1)%5);
		check((num+4)%5);
	}
	sem_post(&mutex);
}

void* philosopher(void* arg)
{
    for(;;) 
	{
        int* num = arg;
        taking_forks(*num);
        putting_forks(*num);
    }
}
 
int main()
{
    pthread_t thds[5]; 
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < 5; i++)
	{
        sem_init(&forks[i], 0, 0);
    }
    for(int i = 0; i < 5; i++) 
	{
        pthread_create(&thds[i], NULL, philosopher, &philos[i]);
    }
    for(int i = 0; i < 5; i++)
	{
        pthread_join(thds[i], NULL);
    }
}