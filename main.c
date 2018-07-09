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
//	int pgsz = getpagesize();
//    float   check;
//	size_t blocksize = 100;
//	ft_printf("void * %d\n", sizeof(void *));
//	ft_printf("t_block * %d\n", sizeof(t_block *));
//	ft_printf("blkStructSz: %zu\n", SBLKSZ);
//	ft_printf("slbStructSz:\t%zu\n", SSLBSZ);
//	ft_printf("tiny combin:\t%zu\n", TNYSZ + SBLKSZ);
//	ft_printf("small combin:\t%zu\n", SMLSZ + SBLKSZ);
//    ft_printf("tiny total:\t%zu\n", (TNYSZ + SBLKSZ) * BLKCNT);
//    ft_printf("small total:\t%zu\n", (SMLSZ + SBLKSZ) * BLKCNT);
//    ft_printf("slab size: %zu\n", SLBSZ);
////    ft_printf("total divided:\t%f\n",  (float)(((SMLSZ + SBLKSZ) * BLKCNT) + (((SMLSZ + SBLKSZ) * BLKCNT)) + SSLBSZ) / 4096.0);
//	while (blocksize < 200) {
//        check = (SSLBSZ) + ((SMLSZ) * blocksize) + ((TNYSZ) * blocksize);
//        printf("%zu - pages: %f\n", blocksize, check / (float)pgsz);
//        blocksize++;
//    }
    char *addr1;
    char *addr3;
    char *addr2;

    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "1Bonjour\n");
    print(addr1);
    addr3 = (char*)realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);

	free(addr1);
    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "2Bonjour\n");
    print(addr1);
    addr2 = (char*)malloc(16*M);
	free(addr2);
    addr3 = (char*)realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);
	free(addr3);
    char *addr;

    addr = malloc(300);
    free(NULL);
    free((void *)addr + 5);
    if (realloc((void *)addr + 32, 10) == NULL)
        print("3Bonjour\n");

    void **center2;
    center2 = malloc(sizeof(void *) * 500);
    for (int i = 0; i < 500; i++)
    {
        if (i % 2 == 0)
        {
            center2[i] = realloc(center2[i - 1], 59);
        }
        else
            center2[i] = malloc(40);
		if (i == 496)
			show_alloc_mem();
    }
	ft_printf("done with 500");
	show_alloc_mem();
    void *mal;
    void *mal2;


    for (int i = 0; i < 128; i++)
    {
        mal = malloc(24);
    }

	void **center;

    char * test = realloc(NULL, 182);
    test[100] = (char)134;
    center = malloc(sizeof(void *) * BLKCNT);
    for (int i = 0; i < 128; i++)
        center[i] = malloc(24);
	for (int i = 0; i < 128; i++)
		free(center[i]);
	for (int i = 0; i < 128; i++)
		center[i] = malloc(200);
	for (int i = 0; i < 128; i++)
		free(center[i]);
	free(center);
    for (int i = 0; i < 128; i++)
    {
        mal = malloc(24);
    }

    mal = malloc(24);
    mal2 = malloc(24);
    free(mal);
    free(mal2);
    void * ret = malloc(200);
    ret = realloc(ret, 19099);
    show_alloc_mem();
    return (0);

}