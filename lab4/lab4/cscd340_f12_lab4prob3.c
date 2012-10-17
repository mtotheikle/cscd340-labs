#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
int sumTo;

void * runner(void * tid)
{	
	printf("Processing thread %d\n", (int) tid);
	int i;
	for (i = 1; i <= sumTo; i++) {
		sum += i;
	}
		printf("sum so far %d\n", sum);
	pthread_exit(NULL);
}

int main(int argsc, char **argv)
{	
	int size = atoi(argv[1]);
	pthread_t tids[size];
	pthread_attr_t attr[size];
	int status, x;
	sumTo = (int) atoi(argv[2]);
	
	for (x = 0; x < size; x++) {
		printf("Creating thread %d\n", x);
		status = pthread_create(&tids[x], NULL, runner, (void *) x);
		
		if (status != 0) {
			exit(-1);
		}
	}
    
	for (x = 0; x < size; x++) {
		pthread_join(tids[x], NULL); // Another thread can run
	}
	
	printf("sum = %d", sum);
	
	return 0;
}