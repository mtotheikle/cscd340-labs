
#include <stdio.h>
#include <string.h>

#define MAX 100

int main(int argc, char* argv[])
{
	FILE * fin;
	fin = fopen("test.txt", "r");
	
	char word[MAX];
	fgets(word, MAX, fin);
	
	while (!feof(fin)) {
		printf("%s", word);
		fgets(word, MAX, fin);
	}
	
	return 0;
}