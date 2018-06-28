#define M (1024 * 1024)
#include <unistd.h>
#include <string.h>
#include "incl/malloc.h"

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
    char *addr1;
    char *addr3;
    char *addr2;

    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "1Bonjour\n");
    print(addr1);
	show_alloc_mem();
    addr3 = (char*)realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);

    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "2Bonjour\n");
    print(addr1);
    addr2 = (char*)malloc(16*M);
    addr3 = (char*)realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);

    char *addr;

    addr = malloc(16);
    free(NULL);
    free((void *)addr + 5);
    if (realloc((void *)addr + 5, 10) == NULL)
        print("3Bonjour\n");

    malloc(1024);
    malloc(1024 * 32);
    malloc(1024 * 1024);
    malloc(1024 * 1024 * 16);
    malloc(1024 * 1024 * 128);
    show_alloc_mem();

    return (0);
}