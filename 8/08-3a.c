#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>

int main()
{
   int     *array;
   int     shmid;
   int     new = 1;
   char    pathname[] = "08-3a.c";
   key_t   key;
   long    i;

   int semid;
   struct sembuf sem;

   if((key = ftok(pathname,0)) < 0){
     printf("Can\'t generate key\n");
     exit(-1);
   }

   semid = semget(key, 1, 0666 | IPC_CREAT);
   

   if(semid < 0) {
	   printf("can't create semaphore\n");
	   exit(-1);
   }

   if((shmid = shmget(key, 4*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
      if(errno != EEXIST){
         printf("Can\'t create shared memory\n");
         exit(-1);
      } else {
         if((shmid = shmget(key, 4*sizeof(int), 0)) < 0){
            printf("Can\'t find shared memory\n");
            exit(-1);
	 }
         new = 0;
      }
   }

   if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
      printf("Can't attach shared memory\n");
      exit(-1);
   }

   sem.sem_num = 0;
   sem.sem_flg = 0;
   if(array[3] != 1) {
           sem.sem_op = 1;
           semop(semid, &sem, 1);
	   array[3] = 1;
   }

   if(new){
      array[0] =  1;
      array[1] =  0;
      array[2] =  1;
   } else {

      sem.sem_op = -1;
      sem.sem_flg = 0;
      sem.sem_num = 0;
      
      semop(semid, &sem, 1);
      
      array[0] += 1;
      for(i=0; i<2000000000L; i++);
      array[2] += 1;

      sem.sem_op = 1;
      sem.sem_flg = 0;
      sem.sem_num = 0;
      semop(semid, &sem, 1);

   }

   array[3] = 0;


   printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
      array[0], array[1], array[2]);

   if(shmdt(array) < 0){
      printf("Can't detach shared memory\n");
      exit(-1);
   }

   semctl(semid, 0, IPC_RMID, 0);

   return 0;
}
