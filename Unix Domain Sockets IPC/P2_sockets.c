//Server

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/Sockets"
#define BUFFER_SIZE 128

int main(int argc, char *argv[]){
    struct sockaddr_un socka;
    int fd;
    int val;
    int fd2;
    unlink(SOCKET_NAME);
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }
    memset(&socka, 0, sizeof(struct sockaddr_un));
    socka.sun_family = AF_UNIX;
    strncpy(socka.sun_path, SOCKET_NAME, sizeof(socka.sun_path) - 1);
    val = bind(fd, (const struct sockaddr *) &socka, sizeof(struct sockaddr_un));
    if (val == -1) {
        perror("Bind Failure");
        exit(EXIT_FAILURE);
    }
    val = listen(fd, 1);
    if (val == -1) {
        perror("listen Failure");
        exit(EXIT_FAILURE);
    }
    fd2 = accept(fd, NULL, NULL);
    if (fd2 == -1) {
        perror("accept Failure");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    printf("Connected With Client\n");
    for(int j = 0; j < 50;){
        printf("\nStrings are:\n");
        for(int i = 0; i < 5; i++){
            val = read(fd2, buffer, BUFFER_SIZE);
            if (val == -1) {
                perror("read system call failure");
                exit(EXIT_FAILURE);
            }
            if(val > 0){
                printf("%s\n", buffer);
                val = write(fd2, buffer, BUFFER_SIZE);
                if (val == -1) {
                    perror("write system call failure");
                    exit(EXIT_FAILURE);
                }
            }
        }
        printf("\nIndexes are:\n");
        char buffer1[BUFFER_SIZE];
        memset(buffer1, 0, BUFFER_SIZE);
        int m = 0;
        for(int i = 0; i < 5; i++){
            val = read(fd2, buffer1, BUFFER_SIZE);
            if (val == -1) {
                perror("read system call failure");
                exit(EXIT_FAILURE);
            }
            if(val > 0){
                printf("%d\n", buffer1[0]);
                if(m < buffer1[0]){
                    m = buffer1[0];
                }
                val = write(fd2, buffer, BUFFER_SIZE);
                if (val == -1) {
                    perror("write system call failure");
                    exit(EXIT_FAILURE);
                }
            }
        }
        char buffer2[BUFFER_SIZE];
        memset(buffer2, 0, BUFFER_SIZE);
        buffer2[0] = m;
        val = write(fd2, buffer2, BUFFER_SIZE);
        if (val == -1) {
            perror("write system call failure");
            exit(EXIT_FAILURE);
        }
        j += 5;
    }
    close(fd2);
    close(fd);
    unlink(SOCKET_NAME);
    return 0;
}