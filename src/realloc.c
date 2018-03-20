#include "../incl/malloc.h"


// get function pointers in here.
// don't fuck around.

static void         update_block(t_block *blk, size_t size, t_mgr *mgr)
{
    mgr->total_allocs += 1;
    mgr->requested_bytes += size;
    blk->data_size = size;
    blk->avail = FALSE;
    if (size > SMLSZ)
        mgr->large_cnt += 1;
}

static void        *findncopy(void *mem, size_t size, t_mgr *mgr, t_block *(fn(t_mgr *, size_t)))
{
    t_block *dst;

	dst = NULL;
    if (!(dst = fn(mgr, size)))
        return (mem);
	mgr->b = (t_block *)mem - 1;
    ft_memcpy(dst + 1, mem, mgr->b->data_size);
    update_block(dst, size, mgr);
    pthread_mutex_unlock(&g_mux);
    free(mem);
    return (dst + 1);
}

void		*realloc(void *mem, size_t size)
{
    t_mgr   *mgr;
    void    *ret;

    ret = NULL;
    pthread_mutex_lock(&g_mux);
    if (!mem || !(mgr = get_mgr(FALSE)))
        return (mem);
    mgr->b = (t_block*)mem - 1;
    if (mgr->b->avail == FALSE)
    {
        if (size <= SMLSZ)
            ret = findncopy(mem, size, mgr, &find_slb_blk);
        else
            ret = findncopy(mem, size, mgr, &find_lrgblk);
    }
	pthread_mutex_unlock(&g_mux);
    return(ret);
}
