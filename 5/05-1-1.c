#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	int fd;
	char string[100];
	if((fd = open("myfile", O_RDONLY)) < 0) {
		printf("Can't open file\n");
		exit(-1);
	}
	if(read(fd, string, 100) < 0) { 
		printf("Can't read string\n");
		exit(-1);
	}
	if(close(fd) < 0) 
		printf("Can't close file\n");

	printf("%s\n", string);
	return 0;
}

