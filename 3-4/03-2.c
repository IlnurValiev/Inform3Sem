#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
	execle("/bin/cat", "/bin/cat", "03-2.c", (char*) NULL, envp);

	printf("ERROR\n");
	exit(-1);
	return 0;
}
