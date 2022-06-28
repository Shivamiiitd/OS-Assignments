//FIFO
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int fd, val, fd1;
    char buffer[128];
    fd = open("/tmp/fifo1", O_RDONLY);
    for(int j = 0; j < 50;){
        printf("\nStrings are:\n");
        for(int i = 0; i < 5; i++){
            val = read(fd, buffer, sizeof(buffer));
            if (val == -1) {
                perror("read system call failure");
                exit(EXIT_FAILURE);
            }
            fflush(stdin);
            printf("%s\n", buffer);
        }
        printf("\nIndexes are:\n");
        char buffer1[128];
        memset(buffer1, 0, 128);
        int m = 0;
        for(int i = 0; i < 5; i++){
            val = read(fd, buffer1, sizeof(buffer1));
            if (val == -1) {
                perror("read system call failure");
                exit(EXIT_FAILURE);
            }
            fflush(stdin);
            printf("%d\n", buffer1[0]);
            if(m < buffer1[0]){
                m = buffer1[0];
            }
        }
        fd1 = open("/tmp/fifo2", O_WRONLY);
        char buffer2[128];
        buffer2[0] = m;
        val = write(fd1, buffer2, 128);
        if (val == -1) {
            perror("write system call failure");
            exit(EXIT_FAILURE);
        }
        j += 5;
    }
    close(fd);
    close(fd1);
    return 0;
}