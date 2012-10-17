#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

void strip(char * s)
{
	int len = strlen(s);
    
	if(s[len - 2] == '\r')
		s[len - 2] = '\0';
    
	else if(s[len - 1] == '\n')
		s[len - 1] = '\0';
    
}// end strip

int parsePipe(char * s, char **leftSide, char ** rightSide)
{
    char *loc = strstr(s, "|");
    if (loc == NULL)
    {
        return -1;
    }
    
    char *l = strtok(s, "|");
    char *r = strtok(NULL, "|");
    
    *leftSide = malloc(sizeof(char *) * strlen(l));
    *rightSide = malloc(sizeof(char *) * strlen(r));
    
    strcpy(*leftSide, l);
    strcpy(*rightSide, r);
    
    return 1;
    
}// end parsePipe

int goAgain(char * s)
{
    if (strcmp(s, "quit") == 0)
        return 0;
    
    return 1;
    
}// end goAgain

int main()
{
	int res;
	char s[MAX];
	char * prePipe = NULL, * postPipe = NULL;
    
	printf("Please enter a string (quit to quit) ");
	fgets(s, MAX, stdin);
	strip(s);
    
	while(goAgain(s))
	{
		res = parsePipe(s, &prePipe, &postPipe);
        
		if(res == -1)
			printf("No PIPE found\n");
        
		else
		{
			printf("prePipe: %s\npostPipe: %s\n\n", prePipe, postPipe);
            
			free(prePipe);
			prePipe = NULL;
			
			free(postPipe);
			postPipe = NULL;
            
		}// end else			
		
		printf("Please enter a string (quit to quit) ");
		fgets(s, MAX, stdin);
		strip(s);
        
	}// end while
    
}// end main
