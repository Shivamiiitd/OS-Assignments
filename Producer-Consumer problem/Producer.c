#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define SYS_writer 449

int main(){
    int x;
    int y;
    x = open("/dev/urandom", O_RDONLY);
    while(1){
        char *data = (char *) malloc(8);
        if(x < 0){
            perror("File Descriptor Error");
            exit(1);
        }
        y = read(x, data, 8);
        data[y] = '\0';
        long m = syscall(SYS_writer, data);
        sleep(1);
    }
}