#include "../incl/malloc.h"

static void        *realloc_tiny(void *mem, t_mgr *mgr)
{
    t_block *dst;
    /*Try to find memory else where*/
    if (!(dst = find_tnyblk(mgr)))
        return (mem);
    ft_memcpy(dst->data, mgr->b->data, TNYSZ);
    free(mem);
    return (dst->data);
}

static void        *realloc_small(void *mem, t_mgr *mgr)
{
    t_block *dst;
    /*Try to find memory else where*/
    if (!(dst = find_smlblk(mgr)))
        return (mem);
    ft_memcpy(dst->data, mgr->b->data, SMLSZ);
    free(mem);
    return (dst->data);
}

static void        *realloc_large(void *mem, size_t size, t_mgr *mgr)
{
    t_block *dst;
    /*Try to find memory else where*/
    if (!(dst = find_lrgblk(mgr, size)))
        return (mem);
    ft_memcpy(dst->data, mgr->b->data, size);
    free(mem);
    return (dst->data);
}

void		*realloc(void *mem, size_t size)
{
    t_mgr   mgr;

    if (!mem || !(mgr.head_slab = get_slabs(&mgr, FALSE)))
        return (mem);
    mgr.b = (t_block*)mem - 1;
    if (size < TNYSZ)
        return (realloc_tiny(mem, &mgr));
    else if (size < SMLSZ)
        return (realloc_small(mem, &mgr));
    else if (size > SMLSZ)
        return (realloc_large(mem, size, &mgr));
    return(mem);
}
