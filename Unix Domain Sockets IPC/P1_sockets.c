//Client

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/Sockets"
#define BUFFER_SIZE 128

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
int main(int argc, char *argv[]){
    struct sockaddr_un socka;
    int val;
    int fd;
    char buffer[BUFFER_SIZE];
    fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }
    memset(&socka, 0, sizeof(struct sockaddr_un));
    socka.sun_family = AF_UNIX;
    strncpy(socka.sun_path, SOCKET_NAME, sizeof(socka.sun_path) - 1);
    val = connect (fd, (const struct sockaddr *) &socka, sizeof(struct sockaddr_un));
    if (val == -1) {
        fprintf(stderr, "Can't connect to Server\n");
        exit(EXIT_FAILURE);
    }
    randstr();
    char *data[5];
    int *index[5];
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
            val = write(fd, data[i], strlen(data[i]));
            if (val == -1) {
                perror("write system call failure");
                exit(EXIT_FAILURE);
            }
            if(val > 0){
                memset(buffer, 0, sizeof(buffer));
                read(fd, buffer, sizeof(buffer));
            }
        }
        for(int i = 0; i < 5; i++){
            val = write(fd, index[i], sizeof(index[i]));
            if (val == -1) {
                perror("write system call failure");
                exit(EXIT_FAILURE);
            }
            if(val > 0){
                memset(buffer, 0, sizeof(buffer));
                read(fd, buffer, sizeof(buffer));
            }
        }
        memset(buffer, 0, sizeof(buffer));
        if (read(fd, buffer, sizeof(buffer)) > 0){
            printf("Highest ID received from P2 is: ");
            printf("%d\n",buffer[0]);
        }
        j += 5;
    }
    buffer[BUFFER_SIZE - 1] = 0;
    close(fd);
    return 0;
}