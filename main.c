#define M (1024 * 1024)
#include <unistd.h>
#include <string.h>
//#include <stdlib.h>
#include "incl/malloc.h"

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
//    char *addr1;
//    char *addr3;
//    char *addr2;
//
//    addr1 = (char*)malloc(16*M);
//    strcpy(addr1, "1Bonjour\n");
//    print(addr1);
//    addr3 = (char*)realloc(addr1, 128*M);
//    addr3[127*M] = 42;
//    print(addr3);
//
//    addr1 = (char*)malloc(16*M);
//    strcpy(addr1, "2Bonjour\n");
//    print(addr1);
//    addr2 = (char*)malloc(16*M);
//    addr3 = (char*)realloc(addr1, 128*M);
//    addr3[127*M] = 42;
//    print(addr3);
//
//    char *addr;
//
//    addr = malloc(16);
//    free(NULL);
//    free((void *)addr + 5);
//    if (realloc((void *)addr + 5, 10) == NULL)
//        print("3Bonjour\n");
//
//    for (int i = 0; i < 500; i++)
//    {
//        if (i % 2 == 0)
//            addr = malloc(42);
//        else
//            addr = malloc(1000);
//    }
    void *mal;
    void *mal2;
    void **center;

    for (int i = 0; i < 128; i++)
    {
        mal = malloc(24);
    }
    center = malloc(sizeof(void *) * BLKCNT);
    for (int i = 0; i < 128; i++)
    {
        center[i] = malloc(24);
    }
    for (int i = 0; i < 128; i++)
    {
        mal = malloc(24);
    }
    for (int i = 0; i < 128; i++)
        free(center[i]);
    free(center);
    mal = malloc(24);
    mal2 = malloc(24);
    free(mal);
    free(mal2);
    show_alloc_mem();
    return (0);
}