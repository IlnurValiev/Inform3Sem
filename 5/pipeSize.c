#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	int fd[2];
	if(pipe(fd) < 0) {
		printf("Can't creat pipe\n");
		exit(-1);
	}
	int i = 0;
	
	for(; write(fd[1], " ", 1); i++) 	
		printf("%d\n", i);
	
}
