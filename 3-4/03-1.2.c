#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv, char* envp) {
 
 	pid_t pid, ppid, chpid;

        chpid = fork();


        pid = getpid();
        ppid = getppid();

	if(chpid == -1) 
		printf("ERROR\n");
	else if(chpid == 0) {
		printf("I am a child process, my pid = %d, my ppid = %d\n", pid, ppid);
		execle("args", "args", "Ilnur Valeiv", (char*) NULL, envp);
	}
	else printf("I am a parent process, my pid = %d, my ppid = %d\n", pid, ppid);
        return 0;
}


