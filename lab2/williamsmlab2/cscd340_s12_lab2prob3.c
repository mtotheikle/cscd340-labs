#include <stdlib.h>

int write(int fd, char *str, int len)
{
    /* do nothing */
	return 0;
}

int syscall(int n, int x, char * str, int s)
{
    asm("mov %0, %%ecx\n"
	   "mov $1, %%ebx\n"
	   "mov $8, %%edx\n"
	   "mov $4, %%eax\n"
	  "int $0x80\n"
	   :
	   : "r" ("goodbye\n")
	);
	
	return 0;
}

int main(int argc, char **argv)
{
    write(1, "hello\n", 6);
    syscall(1, 1, "goodbye\n", 8);
    exit(0);
}

// a) When you compile, link, and run, nothing will print out. Why?
// When I added the write method to the file, nothing was printed because we overwrote the system write method
// todo nothing and just return 0

// b) Now, “goodbye” is printed, while “hello” still isn't. Why?
// goodbye is printed because we are directly calling the syscall method 
// with an argument of 1 which in a 64 bit system is a system call to print the text

// c) When you run the program, nothing is printed. Why?
// Nothing is printed now because in 32-bit mode, the syscall of 1 means exit

// d) What differences in these two files would cause it to print in one case but not the other?
// The difference between /usr/include/asm/unistd_64.h and /usr/include/asm/unistd_32.h is that
// one defines the syscall mappings for 32 while the other is 64-bit

// e) The program doesn't print output in either 32-bit or 64-bit mode. Why?
// The program does not print out anything because the syscall is overwriting
// and just returning 0

// f) The “goodbye” printout is back. Why?
// The assembly prints the "goodbye" because it moves around some memory and assigns it to registers to make
// room for the string of "goodbye\n" then reads the string address of goodby\n which prints it to the string

// g) Can any C function declaration interfere with this variant? Why or why not?
// Yes, if you override the asm declaration things will get ugly
