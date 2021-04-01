#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main() {
	int fd[2], result;
	size_t size;
	char resstring[100];
	char string[] = "Hello, world";

	int semid;
	struct sembuf sem;
	int key = ftok("08-3.c", 0);
	semid = semget(key, 1, 0666 | IPC_CREAT); 

	if(pipe(fd) < 0) {
		printf("Can't create pipe\n");
		exit(-1);
	}
	result = fork();
	if(result < 0) {
		printf("Can't fork child\n");
		exit(-1);
	}
	else if (result == 0) {
		close(fd[0]);
		size = write(fd[1], string, sizeof(string)/sizeof(char)+1);
		if(size != sizeof(string)/sizeof(char)+1) {
			printf("Can't write all string\n");
			exit(-1);
		}
		close(fd[1]);
		printf("Child exit\n");

		sem.sem_flg = 0;
		sem.sem_num = 0;
		sem.sem_op = 1;
		semop(semid, &sem, 1);
	}
	else {
		sem.sem_flg = 0;
		sem.sem_num = 0;
		sem.sem_op = -1;
		semop(semid, &sem, 1);

		close(fd[1]);
		size = read(fd[0], resstring, sizeof(string)/sizeof(char)+1);
		if(size <0) {
			printf("Can't read string\n");
			exit(-1);
		}
		printf("%s\n", resstring);
		close(fd[0]);
	}
	return 0;
}
		
