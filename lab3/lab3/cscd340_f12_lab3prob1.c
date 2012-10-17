//
//  main.c
//  lab3
//
//  Created by Michael Williams on 10/9/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{

    int fd[2];
    // If it does not work a -1 will be returned
    pipe(fd);
    
    pid_t pid = fork();
    
    if (pid == -1)  
        return -1; 
    
    if (pid != 0)  
    {  
        
        close(fd[0]); //close read from pipe, in parent
        dup2(fd[1], STDOUT_FILENO); // Replace stdout with the write end of the pipe
        close(fd[1]); // Don't need another copy of the pipe write end hanging about
        execlp("ls", "ls", "-la", NULL);
    }
    else
    {
        close(fd[1]); //close write to pipe, in child
        dup2(fd[0], STDIN_FILENO); // Replace stdin with the read end of the pipe
        close(fd[0]); // Don't need another copy of the pipe read end hanging about
        execlp("wc", "wc", "-w", NULL);
    } 
}

// 1)
//      a. micahel-williams:lab3 Mike$ ./a.out
//          56
//
//      b. micahel-williams:lab3 Mike$ ./a.out
//          56