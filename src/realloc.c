#include "../incl/malloc.h"

static void         update_block(t_block *blk, size_t size, t_mgr *mgr)
{
    mgr->head_slab->total_allocs += 1;
    mgr->head_slab->requested_bytes += size;
    blk->data_size = size;
    blk->avail = FALSE;
    if (size > SMLSZ)
        mgr->head_slab->large_cnt += 1;
}

static void        *realloc_tiny(void *mem, size_t size, t_mgr *mgr)
{
    t_block *dst;
    /*Try to find memory else where*/
    if (!(dst = find_tnyblk(mgr)))
        return (mem);
    ft_memcpy(dst->data, mgr->b->data, size);
    free(mem);
    update_block(dst, size, mgr);
    return (dst->data);
}

static void        *realloc_small(void *mem, size_t size, t_mgr *mgr)
{
    t_block *dst;
    /*Try to find memory else where*/
    if (!(dst = find_smlblk(mgr)))
        return (mem);
    ft_memcpy(dst->data, mgr->b->data, size);
    free(mem);
    update_block(dst, size, mgr);
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
    update_block(dst, size, mgr);
    return (dst->data);
}

void		*realloc(void *mem, size_t size)
{
    t_mgr   mgr;

    if (!mem || !(mgr.head_slab = get_slabs(&mgr, FALSE)))
        return (mem);
    mgr.b = (t_block*)mem - 1;
    if (size < TNYSZ)
        return (realloc_tiny(mem, size, &mgr));
    else if (size < SMLSZ)
        return (realloc_small(mem, size, &mgr));
    else if (size > SMLSZ)
        return (realloc_large(mem, size, &mgr));
    return(mem);
}
