#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#define MAX 100

// IMPORTANT NOTE:
// The more command can currently cause for some unexpected behavior as the main
// parent is not currently waiting correctly. This will get fixed in the HW - Michael

void strip(char * s)
{
	int len = strlen(s);
    
	if(s[len - 2] == '\r')
		s[len - 2] = '\0';
    
	else if(s[len - 1] == '\n')
		s[len - 1] = '\0';
}// end strip

int makeargs(char *s, char *** argv)
{
    // http://www.cplusplus.com/reference/clibrary/cstring/strtok/
    int length = (int) strlen(s);
    if (length < 1) {
        return -1; // no args
    }
    
    int i;
    int count = 1; // count starts at 1 as we assume there is always one arguemnt
    for (i = 0; i < length; i++) {
        if (s[i] == ' ') {
            count++;
        }
    }
    
    *argv = calloc(count, sizeof(char*));
	char * token = strtok(s, " ");
    i = 0;
    while (token != NULL) {
        (*argv)[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    
    return count;
    
}// end makeArgs

void clean(int argc, char **argv)
{
    int i;
    for (i = 0; i < argc; i++) {
        free(argv[i]);
        argv[i] = NULL;
    }
    
    free(argv);
}

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);
}

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

void forkMe(char **left, char **right)
{
    char **args1 = NULL;
    int argsc1 = makeargs(*left, &args1);
    
    char **args2 = NULL;
    int argsc2 = makeargs(*right, &args2);
    
    if (fork() != 0)
    {
        int status;
        waitpid(-1, &status, 0);
        
        clean(argsc1, args1);
        clean(argsc2, args2);
    }
    else {
        
        int fd[2];
        // If it does not work a -1 will be returned
        pipe(fd);
        
        pid_t pid = fork();
        if (pid == -1) 
            return;
        
        if (pid != 0)  
        {  
            close(fd[0]); //close read from pipe, in parent
            dup2(fd[1], STDOUT_FILENO); // Replace stdout with the write end of the pipe
            close(fd[1]); // Don't need another copy of the pipe write end hanging about
            execvp(args1[0], args1);
            
            // Somethign failed, bail
            exit(0);
        }
        else
        {
            close(fd[1]); //close write to pipe, in child
            dup2(fd[0], STDIN_FILENO); // Replace stdin with the read end of the pipe
            close(fd[0]); // Don't need another copy of the pipe read end hanging about
            execvp(args2[0], args2);
            
            // Something failed, bail
            exit(0);
        }
    }      
}

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
            
            forkMe(&prePipe, &postPipe);
            
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