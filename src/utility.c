#include "../incl/malloc.h"

int     slab_len(t_slab *list)
{
    int i;

    i = 0;
    while (list && ++i){
        list = list->next;
    }
    return (i);
}