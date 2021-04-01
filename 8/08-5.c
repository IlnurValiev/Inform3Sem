#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#define N 5

int main() {
	int fd[2], result, fd1[2];
	size_t size, size1;
	char resstring[100];
	char resstring1[100];

	char string[] = "Hello, world";
	char string_1[] = "Goodbye, world";

	int semid;
	struct sembuf sem;
	char path[] = "08-5.c";
	key_t key;
	key = ftok(path, 0);
	semid = semget(key, 1, 0666 | IPC_CREAT);

	if(pipe(fd) < 0) {
		printf("Can't create pipe 1\n");
		exit(-1);
	}
	if(pipe(fd1) < 0) {
		printf("Can't create pipe 2\n");
		exit(-1);
	}

	result = fork();

	for(int i = 1; i <= N; i++) {

		if(result < 0) {
			printf("Can't fork child\n");
			exit(-1);
		}

		else if (result > 0) {
			size = write(fd[1], string_1, sizeof(string_1)/sizeof(char)+1);
			if(size != sizeof(string_1)/sizeof(char)+1) {
				printf("Can't write all string\n");
				exit(-1);
			}

			size1 = read(fd1[0], resstring1, sizeof(string)/sizeof(char)+1);
			if(size1 < 0) {
				printf("Can't read string\n");
				exit(-1);
			}
			printf("Parent procces: %s %d\n", resstring1, i);

		
			sem.sem_num = 0;               
			sem.sem_flg = 0;
			sem.sem_op = 1;
			semop(semid, &sem, 1);
		}
		else {
			size1 = write(fd1[1], string, sizeof(string)/sizeof(char)+1);
			if(size1 != sizeof(string)/sizeof(char)+1) {
				printf("Can't write all string\n");			
				exit(-1);
			}

			sem.sem_num = 0;
			sem.sem_flg = 0;		
			sem.sem_op = -1;
			semop(semid, &sem, 1);

			size = read(fd[0], resstring, sizeof(string_1)/sizeof(char)+1);
			if(size < 0) {
				printf("Can't read string\n");
				exit(-1);
			}
                
			printf("Child procces: %s %d\n", resstring, i);
			printf("\n");

		}
	}
	semctl(semid, 0, IPC_RMID, 0);

	return 0;

}
		
