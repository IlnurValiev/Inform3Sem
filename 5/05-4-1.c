#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main() {
	int fd;
	size_t size;
	char name[] = "file.fifo";
	umask(0);
	if(mknod(name, S_IFIFO | 0666, 0) < 0) {
		printf("Can't create FIFO\n");
		exit(-1);
	}
	fd = open(name, O_WRONLY);
	if(fd < 0) {
		printf("Can't open FIFO\n");
		exit(-1);
	}
	size = write(fd, "Vadim", 6);
	if(size != 6) {
		printf("Can't write all string\n");
		exit(-1);
	}
	return 0;
}
