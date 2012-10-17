#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * sayHello(void * tid)
{
	printf("Hello from thread: %d\n", (int) tid);
	pthread_exit(NULL);
}

int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("Please enter an arguement for how many threads to create\n");
		
		exit(0);
	}
	
	int size = atoi(argv[1]);
	pthread_t tids[size];
	int status, x;
	
	for (x = 0; x < size; x++) {
		status = pthread_create(&tids[x], NULL, sayHello, (void *)x);
		pthread_join(tids[x], NULL); // Another thread can run
		
		if (status != 0) {
			exit(-1);
		}
	}
	
	return 0;
}