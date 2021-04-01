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
 
    struct query_str {
	    long type;
	    pid_t pid;
    };

    struct query_str query;

    struct answer_str {
	    long type;
	    char msg[81];
    };

    struct answer_str answer;

    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }
    
    while(1) {

 	if ((msgrcv(msqid, (struct query_str *) &query, maxlen, 1, 0)) < 0) {
        	printf("Can\'t receive message from queue\n");
       	  	exit(-1);
       	}

      	answer.type = query.pid;
	strcpy(answer.msg, "Happy New Year from server!");
	
	if (msgsnd(msqid, (struct answer_str *) &answer, maxlen, 0) < 0){
        	 printf("Can\'t send message to queue\n");
        	 msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        	 exit(-1);
       }
    }

    return 0;    
}
