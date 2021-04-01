#include <stdio.h>

int main(int argc, char* argv[], char* a[]) {

	int i;
	for(i = 0; a[i] != NULL; i++) 
		printf("%s\n", a[i]);
	
	printf("\nargc = %d\n", argc);
        
	for(i = 0; i < argc; i++) 
		printf("%s ", argv[i]);
	printf("\n");

	return 0;	
}
