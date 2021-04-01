#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void enter(int* turn, int* interest_self, int* interest_other) {
    *turn = 1;
    *interest_self = 1;
    while(*interest_other && *turn == 1);
}

void leave(int* interest_self) {
    *interest_self = 0;
}

int main()
{
   int     *array;
   int     shmid;
   int     new = 1;
   char    pathname[] = "4a.c";
   key_t   key;
   long    i;

   if((key = ftok(pathname,0)) < 0){
     printf("Can\'t generate key\n");
     exit(-1);
   }

   if((shmid = shmget(key, 6*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
      if(errno != EEXIST){
         printf("Can\'t create shared memory\n");
         exit(-1);
      } else {
         if((shmid = shmget(key, 6*sizeof(int), 0)) < 0){
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

   if(new) {
      array[0] =  1;
      array[1] =  0;
      array[2] =  1;
   } else {
      enter(&array[3], &array[5], &array[4]);
      
      array[0] += 1;
      for(i=0; i<2000000000L; i++);
      array[2] += 1;

      leave(&array[5]);
   }

   printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
      array[0], array[1], array[2]);

   if(shmdt(array) < 0){
      printf("Can't detach shared memory\n");
      exit(-1);
   }
    printf("shmid = %d\n", shmid);
   return 0;
}
