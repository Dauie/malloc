#include "../incl/malloc.h"

void        clean_allocations(t_mgr *mgr)
{
    t_slab  *tmp;
    t_slab  *head;
    t_slab  *tail;

    head = mgr->head_slab;
    tail = NULL;
    while (head)
    {
        if (head->tiny_avail == BLKCNT && head->small_avail == BLKCNT)
        {
            tmp = head;
            if (head == mgr->head_slab)
                mgr->head_slab = mgr->head_slab->next;
            if (tail)
                tail->next = head->next;
            head = head->next;
            munmap(tmp, SLBSZ);
        }
        else
        {
            tail = head;
            head = head->next;
        }
    }
}