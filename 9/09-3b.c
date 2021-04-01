#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    
    int msqid;
    char pathname[]="09-1a.c";
    key_t  key;
    int len, maxlen;

    maxlen = 81;

    struct mymsgbuf
    {
       long mtype;
       char mtext[81];
    } mybuf;
 
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }

    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0) {
         printf("Can\'t receive message from queue\n");
         exit(-1);
       }

    printf("Type = %ld, text = %s\n", mybuf.mtype, mybuf.mtext);


       
    mybuf.mtype = 2;
    strcpy(mybuf.mtext, "Happy New Year from 2 programm!");
    len = strlen(mybuf.mtext)+1;
       
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
       }

       
    return 0;    
}
