//Message Queues
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
  
struct msg_string {
    long msg_type;
    char msg_data[50];
};
  
int main()
{
    int msg_id, msg_id1;
    struct msg_string message;
    msg_id = msgget((key_t)10, 0666 | IPC_CREAT);
    for(int j = 0; j < 50;){
        printf("\nStrings are:\n");
        for(int i = 0; i < 5; i++){
            msgrcv(msg_id, &message, sizeof(message), 1, 0);
            printf("%s\n", message.msg_data);
        }
        int m = 0;
        printf("\nIndexes are:\n");
        for(int i = 0; i < 5; i++){
            msgrcv(msg_id, &message, sizeof(message), 1, 0);
            printf("%s\n", message.msg_data);
            if(m < atoi(message.msg_data)){
                m = atoi(message.msg_data);
            }
        }
        char val[20][20];
        sprintf(val[0], "%d", m);
        strcpy(message.msg_data, val[0]);
        printf("%s\n", message.msg_data);
        msg_id1 = msgget((key_t)11, 0666 | IPC_CREAT);
        msgsnd(msg_id1, &message, sizeof(message), 0);
        j += 5;
    }
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}