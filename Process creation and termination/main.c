#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h> 

int cont(int a, int b){
    char s1[20];
    char s2[20];
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
    strcat(s1, s2);
    int c = atoi(s1);
    return c;
}

void cal_average(char sec){
    int x;
    int y;
    char *s = (char *) calloc(1000, sizeof(char));
    x = open("student_record.csv", O_RDONLY);
    if(x < 0){
        perror("r1");
        exit(1);
    }
    y = read(x, s, 1000);
    s[y] = '\0';

    int count = 0;
    for(int i = 98; i < 815; i++){
        if(s[i] == sec){
            count++;
        }
    }

    int netsum[] = {0, 0, 0, 0, 0, 0};
    for(int j = 98; j < 815; j++){
        if(s[j] == sec){
            int m = 3;
            for(int i = 0; i < 6; i++){

                if(s[j+m] == ','){
                    int x1 = s[j+m-1] - 48;
                    netsum[i] += x1;
                    m += 2;
                }

                else if(s[j+m+2] == ','){
                    int a1 = s[j+m-1] - 48;
                    int b1 = s[j+m] - 48;
                    int c1 = s[j+m+1] - 48;
                    int d1 = cont(a1, b1);
                    int e1 = cont(d1,c1);
                    netsum[i] += e1;
                    m += 4;
                }

                else{
                    int a1 = s[j+m-1] - 48;
                    int b1 = s[j+m] - 48;
                    int c1 = cont(a1, b1);
                    netsum[i] += c1;
                    m += 3;
                }
            }
        }
    }
    printf("-----------------------\n");
    printf("Average Score of Assignments for Section %c are: \n", sec);
    printf("Assignment 1: %f\n",(float)netsum[0]/count);
    printf("Assignment 2: %f\n",(float)netsum[1]/count);
    printf("Assignment 3: %f\n",(float)netsum[2]/count);
    printf("Assignment 4: %f\n",(float)netsum[3]/count);
    printf("Assignment 5: %f\n",(float)netsum[4]/count);
    printf("Assignment 6: %f\n",(float)netsum[5]/count);
    printf("-----------------------\n");
    
}

int main(int argc, char *argv[]){

    pid_t n;
    n = fork();
    if(n == 0){
        //Child Process
        cal_average('A');
    }
    else if(n < 0){
        printf("Error");
    }
    else{
        //Parent Process
        int status;
        waitpid(n, &status, 0);
        cal_average('B');
    }
    exit(0);
    return 0;
}