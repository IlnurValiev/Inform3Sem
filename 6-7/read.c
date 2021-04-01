#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
   char *array;
   int shmid;
   char file_name[] = "write.c";

   key_t key = ftok(file_name, 0);
   
   if(key < 0) {
       printf("Can't generate key\n");
       exit(-1);
   }

    shmid = shmget(key, 0, 0);

    if(shmid < 0) {
        printf("Can't find shared memory\n");
        exit(-1);
    }

    array = shmat(shmid, NULL, 0);
    
    if(array < 0) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    printf("%s\n", array);
    
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
