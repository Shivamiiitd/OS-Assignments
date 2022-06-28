#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h> 
#include<pthread.h>

int cont(int a, int b){
    char s1[20];
    char s2[20];
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
    strcat(s1, s2);
    int c = atoi(s1);
    return c;
}

void cal_average(char sec, int arr[]){
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
            arr[6]++;
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
                    arr[i] += x1;
                    m += 2;
                }

                else if(s[j+m+2] == ','){
                    int a1 = s[j+m-1] - 48;
                    int b1 = s[j+m] - 48;
                    int c1 = s[j+m+1] - 48;
                    int d1 = cont(a1, b1);
                    int e1 = cont(d1,c1);
                    netsum[i] += e1;
                    arr[i] += e1;
                    m += 4;
                }

                else{
                    int a1 = s[j+m-1] - 48;
                    int b1 = s[j+m] - 48;
                    int c1 = cont(a1, b1);
                    netsum[i] += c1;
                    arr[i] += c1;
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

void *pointer(void *arg){
    char sec = 'A';
    cal_average(sec, (int *)arg);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int arr[] = {0, 0, 0, 0, 0, 0, 0};
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &pointer, arr);
    pthread_join(thread_id, NULL);
    cal_average('B', arr);
    printf("-----------------------\n");
    printf("Average Score of Assignments for both Sections are: \n");
    printf("Assignment 1: %f\n",(float)arr[0]/arr[6]);
    printf("Assignment 2: %f\n",(float)arr[1]/arr[6]);
    printf("Assignment 3: %f\n",(float)arr[2]/arr[6]);
    printf("Assignment 4: %f\n",(float)arr[3]/arr[6]);
    printf("Assignment 5: %f\n",(float)arr[4]/arr[6]);
    printf("Assignment 6: %f\n",(float)arr[5]/arr[6]);
    printf("-----------------------\n");
    exit(0);
    pthread_exit(NULL);
    return 0;
}