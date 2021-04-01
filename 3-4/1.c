#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid, ppid;
	
	pid = getpid();
	ppid = getppid();
	
	printf("My pid = %d, my ppid = %d\n", pid, ppid);
	return 0;
}

