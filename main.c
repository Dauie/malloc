#define M (1024 * 1024)
#include <unistd.h>
#include <string.h>
//#include <stdlib.h>
#include "incl/malloc.h"
#include "libft/incl/printf.h"
#include <stdio.h>

//void print(char *s)
//{
//    write(1, s, strlen(s));
//}

int main()
{
	int pgsz = getpagesize();
    float   check;
	size_t blocksize = 100;
	ft_printf("blkStructSz: %zu\n", SBLKSZ);
	ft_printf("slbStructSz:\t%zu\n", SSLBSZ);
	ft_printf("tiny combin:\t%zu\n", TNYSZ + SBLKSZ);
	ft_printf("small combin:\t%zu\n", SMLSZ + SBLKSZ);
    ft_printf("tiny total:\t%zu\n", (TNYSZ + SBLKSZ) * BLKCNT);
    ft_printf("small total:\t%zu\n", (SMLSZ + SBLKSZ) * BLKCNT);
    ft_printf("slab size: %zu\n", SLBSZ);
//    ft_printf("total divided:\t%f\n",  (float)(((SMLSZ + SBLKSZ) * BLKCNT) + (((SMLSZ + SBLKSZ) * BLKCNT)) + SSLBSZ) / 4096.0);
	while (blocksize < 512) {
        check = (SSLBSZ) + ((SMLSZ) * blocksize) + ((TNYSZ) * blocksize);
        printf("%zu - pages: %f\n", blocksize, check / (float)pgsz);
        blocksize++;
    }
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
//    void *mal;
//    void *mal2;
//    void **center;
//
//    for (int i = 0; i < 128; i++)
//    {
//        mal = malloc(24);
//    }
//    center = malloc(sizeof(void *) * BLKCNT);
//    for (int i = 0; i < 128; i++)
//    {
//        center[i] = malloc(24);
//    }
//    for (int i = 0; i < 128; i++)
//    {
//        mal = malloc(24);
//    }
//    for (int i = 0; i < 128; i++)
//        free(center[i]);
//    free(center);
//    mal = malloc(24);
//    mal2 = malloc(24);
//    free(mal);
//    free(mal2);
//    show_alloc_mem();
//    return (0);
}