#include<stdio.h>
#include<stdint.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>

int a = 0;

//RDRAND instruction
int rdrand_num(uint64_t *rand){
	unsigned char ok;
	asm volatile ("rdrand %0; setc %1"
		: "=r" (*rand), "=qm" (ok));
	return (int) ok;
}

void sigalrm_handler(int signum){
    printf("In SR SIGALRM handler\n");
    int *x = (int*)rdrand_num;
    int m = rand();
    union sigval value;
    value.sival_int += *x + m;
    if(sigqueue(a, SIGTERM, value) != 0){
        perror("sigqueue Error");
        exit(1);
    }
}

int main(int argc, char **argv){
    int x = atoi(argv[1]);
    a = x;
    signal(SIGALRM, sigalrm_handler);
    struct itimerval time;
    time.it_value.tv_sec = 1; // Time interval is 1 second
    time.it_value.tv_usec = 0;	
    time.it_interval = time.it_value;
    if (setitimer(ITIMER_REAL, &time, NULL) == -1) {
        perror("setitimer Error");
        exit(1);
    }
    while(1){
        pause();
    }
    return 0;
}
