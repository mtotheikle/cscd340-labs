#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int compareToInt(const void *a, const void *b)
{
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    
    return *ia  - *ib;
}

int compareToChar(const void *a, const void *b)
{
    const char *ia = (const char *)a;
    const char *ib = (const char *)b;

    return strcmp(ia, ib);
}

int main()
{    
    int i;
    
    int integers[20] = {7, 3, 4, 1, -1, 23, 12, 43, 2, -4, 5, 23, 56, 42, 90, 10, -12, 67, 90, 4};    
    char characters[20] = {'g', 'q', 'a', 'h', 'k', 'l', 'o', 'p', 'z', 'd', 'e', 
        'u', 'l', 'p', 'm', 'v', 'A', 'x', 't', 'Z'};
    
    printf("Original array of integers:\n");
    for(i = 0; i < 20; i++) 
        printf("%d | ", integers[i]);
    printf("\n\n");
    
    printf("Original array of characters:\n");
    for(i = 0; i < 20; i++) 
        printf("%c | ", characters[i]);
    printf("\n\n");
    
    /* sort array using qsort functions */ 
    qsort(integers, 20, sizeof(int), compareToInt);
    
    printf("Sorted array of integers:\n");
    for(i = 0; i < 20; i++) 
        printf("%d | ", integers[i]);
    
    printf("\n\n");

    printf("Original array of characters:\n");
    qsort(characters, 20, sizeof(char), compareToChar);
    
    for(i = 0; i < 20; i++) 
        printf("%c | ", characters[i]);
}