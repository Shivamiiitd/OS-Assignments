#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define SYS_reader 448

int main(){
    int x;
    while(1){
        char *data = (char *) calloc(8, sizeof(char));
        long m = syscall(SYS_reader, data);
        printf("Random Numbers received from /dev/urandom are: \n");
        for(int i = 0; i < 8; i++){
            printf("%d\n", data[i]);
        }
        printf("\n");
        sleep(1);
    }
}