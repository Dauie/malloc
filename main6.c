#include "incl/malloc.h"

#define M (1024 * 1024)


void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr;

	addr = malloc(16);
	print("bing\n");
	free(NULL);
	print("bong\n");
	free((void *)addr + 5);
	print("ching\n");
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjour\n");
	print("chong\n");
}