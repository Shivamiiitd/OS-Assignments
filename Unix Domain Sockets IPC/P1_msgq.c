//Message Queues
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

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
struct msg_string {
    long msg_type;
    char msg_data[50];
};
  
int main()
{
    int msg_id, msg_id1;
    struct msg_string message; 
    msg_id = msgget((key_t)10, 0666 | IPC_CREAT);
    message.msg_type = 1;
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
            strcpy(message.msg_data, data[i]);
            msgsnd(msg_id, &message, sizeof(message), 0);
        }
        for(int i = 0; i < 5; i++){
            char val[20][20];
            sprintf(val[i], "%d", *index[i]);
            strcpy(message.msg_data, val[i]);
            msgsnd(msg_id, &message, sizeof(message), 0);
            memset(val, 0, sizeof(val));
        }
        msg_id1 = msgget((key_t)11, 0666 | IPC_CREAT);
        msgrcv(msg_id1, &message, sizeof(message), 1, 0);
        printf("Highest ID received from P2 is: %s\n", message.msg_data);
        j += 5;
    } 
    msgctl(msg_id1, IPC_RMID, NULL);
    return 0;
}