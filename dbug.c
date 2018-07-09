
#include "incl/malloc.h"

int 		main(void)
{
	void **allocs;

	allocs =  malloc(sizeof(char *) * 3);
	for (int i = 0; i < 3; i++)
		allocs[i] =  malloc(1024);
	show_alloc_mem();
	for (int i = 0; i < 3; i++)
	 	free(allocs[i]);
	for (int i = 0; i < 3; i++)
		allocs[i] = malloc(2048);
	for (int i = 0; i < 3; i++)
		free(allocs[i]);
	show_alloc_mem();
}