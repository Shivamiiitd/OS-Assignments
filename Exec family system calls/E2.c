#include<stdio.h>
#include<assert.h>
#include<stdint.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<string.h>
int a = 0;
int pid = 0;
double cpu_freq = 2894.563; //MHz 
uint64_t start;
long long n = 0;

//RDTSC instruction
unsigned old, new;
static __inline__ unsigned long long rdtsc(void){
    __asm__ __volatile__ ("RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (new), "=r" (old)::
        "%rax", "rbx", "rcx", "rdx");
}

void sigalrm_handler(int signum){
    rdtsc();
    start = ( ((uint64_t)new << 32) | old );
    printf("IN ST SIGALRM handler\n");
    kill(pid, SIGTERM);
}

void sigterm_handler(int signum){
    printf("IN ST SIGTERM handler\n");
    printf("Random number generated from RDTSC is %llu\n", start); //Clock ticks
    n = (start / cpu_freq) / 1000000; // Divide by 10^6 as frequency was in MegaHertz
    int p = n / 3600; // 1 hour = 3600 seconds
    int q = n - 3600*p;
    int r = q / 60; // 1 minute = 60 seconds
    int t = q - 60*r;
    printf("Time Elapsed is %d hours %d minutes %d seconds\n",p ,r, t);
}

int main(int argc, char **argv){
    int x = atoi(argv[1]);
    pid = getpid();
    a = x;
    signal(SIGTERM, sigterm_handler);
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