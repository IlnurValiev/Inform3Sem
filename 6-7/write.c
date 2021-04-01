#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1000000

int main()
{


    char file_name[] = "write.c";
    char send_line[SIZE];
    
    int fd;
    fd = open(file_name, O_RDONLY);
    read(fd, send_line, SIZE);
    
    size_t size = sizeof(send_line)/sizeof(char);

    char *array;
    int shmid;
    key_t key = ftok(file_name, 0);

    if(key < 0) {
       printf("Can't generate key\n");
       exit(-1);
    }

    shmid = shmget(key, size, 0666 | IPC_CREAT);
   
    if(shmid < 0) {
       printf("Can't create shared memory\n");
       exit(-1);
    }
    
    array = shmat(shmid, NULL, 0);   

    if(array < 0) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    for(int i = 0; i < size; i++)
        array[i] = send_line[i];

    return 0;
}






