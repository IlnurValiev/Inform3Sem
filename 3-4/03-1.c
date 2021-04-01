#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	pid_t pid, ppid;
	
	int a = 0;

	fork();

	a++;

	pid = getpid();
	ppid = getppid();
		
	printf("My pid = %d, my ppid = %d, a = %d\n", pid, ppid, a);

	sleep(1);		
	return 0;
}

