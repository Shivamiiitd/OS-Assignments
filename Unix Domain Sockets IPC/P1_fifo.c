//FIFO
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char *randomstrings[50];
char letter;

void randstr(){
    for (int i = 0; i < 50; i++) {
        int len = 6;
        randomstrings[i] = malloc(len + 1);
        for(int j = 0; j < len; j++)
        {
            letter = 'A' + (rand() % 26);
            randomstrings[i][j] = letter;
        }
        randomstrings[i][len] = '\0';
    }
}

int main(){
    int fd, fd1, val, val2, val3;
    char buffer[128];
    fflush(stdin);
    val = mkfifo("/tmp/fifo1", 0666);
    val3 = mkfifo("/tmp/fifo2", 0666);
    fd = open("/tmp/fifo1", O_WRONLY);
    char *data[5];
    int *index[5];
    randstr();
    for(int j = 0; j < 50;){
        data[0] = randomstrings[j];
        data[1] = randomstrings[j+1];
        data[2] = randomstrings[j+2];
        data[3] = randomstrings[j+3];
        data[4] = randomstrings[j+4];
        index[0] = malloc(2);
        index[1] = malloc(2);
        index[2] = malloc(2);
        index[3] = malloc(2);
        index[4] = malloc(2);
        *index[0] = j;
        *index[1] = j+1;
        *index[2] = j+2;
        *index[3] = j+3;
        *index[4] = j+4;
        for(int i = 0; i < 5; i++){
            val2 = write(fd, data[i], sizeof(buffer));
            if (val2 == -1) {
                perror("write system call failure");
                exit(EXIT_FAILURE);
            }
        }
        for(int i = 0; i < 5; i++){
            val2 = write(fd, index[i], sizeof(buffer));
            if (val2 == -1) {
                perror("write system call failure");
                exit(EXIT_FAILURE);
            }
        }
        fd1 = open("/tmp/fifo2", O_RDONLY);
        char buffer2[128];
        val2 = read(fd1, buffer2, sizeof(buffer));
        if (val2 == -1) {
            perror("read system call failure");
            exit(EXIT_FAILURE);
        }
        printf("Highest ID received from P2 is: ");
        printf("%d\n",buffer2[0]);
        j += 5;
    }
    close(fd);
    close(fd1);
    return 0;
}