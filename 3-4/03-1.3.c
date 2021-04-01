#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
	
	pid_t pid, ppid, chpid;
	
	chpid = fork();

	pid = getpid();
	ppid = getppid();
	
	switch(chpid) {
		
		case -1:	
			printf("ERROR\n");
			break;
		
		case 0:
			printf("I am a child process, my PID = %d, my PPID = %d\n", pid, ppid);
			execle("args", "args", "Ilnur Valiev", (char* ) NULL, envp);
			break;
		
		default:
			printf("I am a parent process, my PID = %d, my PPID = %d\n", pid, ppid);
	}

	return 0;
}

