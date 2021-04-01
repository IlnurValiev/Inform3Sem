#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy) {

   pthread_t mythid;
   
   mythid = pthread_self();

   a = a+5;

   printf("Thread %u, Calculation result = %d\n", (unsigned int)mythid, (int)a);

   return NULL;
}

void *mythread_1(void *dummy) {

   pthread_t mythid;

   mythid = pthread_self();

   a = a+10;

   printf("Thread %u, Calculation result = %d\n", (unsigned int)mythid, (int)a);

   return NULL;
}


int main()
{
   pthread_t thid_1, thid_2, mythid; 
   int result_1, result_2;

   result_1 = pthread_create(&thid_1, (pthread_attr_t *)NULL, mythread, NULL);
  
   if(result_1 != 0){
      printf ("Error on thread 1 create, return value = %d\n", result_1);
      exit(-1);
   }  
   
   result_2 = pthread_create(&thid_2, (pthread_attr_t *)NULL, mythread_1, NULL);
   
   if(result_2 != 0) {
       printf("Error on thread 2 create, return value = %d\n", result_2);
   }
   
   printf("Threads created, thid 1 = %u, thid 2 = %u\n", (unsigned int)thid_1, (unsigned int)thid_2);

   mythid = pthread_self();
   
   a = a+1;
   
   printf("Thread %u, Calculation result = %d\n", (unsigned int)mythid, a);

   pthread_join(thid_1, (void **)NULL);
   pthread_join(thid_2, (void **)NULL);

   return 0;
}
