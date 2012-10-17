#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 100

int main(int argc, char* argv[])
{
	int fd;
	
	FILE * fin;
	fin = fopen("test.txt", "r");
	
	char word[MAX];
	fgets(word, MAX, fin);
	
	while (!feof(fin)) {
		fgets(word, MAX, fin);
	}
	
	return 0;
}