#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<fcntl.h>

void sigterm_handler(int signum, siginfo_t *data, void *addi){
    int _val = data->si_value.sival_int;
    printf("In S1 SIGTERM Handler\n");
    printf("Random Number generated from RDRAND is: %lld\n", _val);
    printf("\n");
}

char pid[20];
int main(){
    pid_t S1;
    pid_t SR;
    pid_t ST;
    S1 = fork();
    if(S1 < 0){
        perror("Error while creating S1\n");
        exit(1);
    }
    if(S1 == 0){
        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        act.sa_sigaction = &sigterm_handler;
        if (sigaction(SIGTERM, &act, NULL) == -1) {
            perror("Error while calling S1 SIGTERM handler\n");
            exit(1);
        }
        while(1){
            pause();
        }    
    }
    else if(S1 > 0){
        sprintf(pid, "%d", S1);
        SR = fork();
        if(SR < 0){
            perror("Error while creating SR\n");
            exit(1);
        }
        if(SR == 0){
            char *args[] = {"./sr", pid, NULL}; //Passing the pid of S1 in E1
            execvp(args[0], args); // Launching E1 from SR
        }
        if(SR > 0){
            ST = fork();
            if(ST < 0){
                perror("Error while creating ST\n");
                exit(1);
            }
            if(ST == 0){
                char *args[] = {"./st", pid, NULL}; //Passing the pid of S1 in E2
                execvp(args[0], args); // Launching E2 from ST
            }
        }
    }
    return 0;
}