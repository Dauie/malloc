/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:56:34 by rlutt             #+#    #+#             */
/*   Updated: 2018/03/20 11:21:33 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void update_mgr(t_mgr *mgr, size_t req) {
	mgr->requested_bytes += req;
	mgr->total_allocs += 1;
}

static void *alloc_large(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_lrgblk(mgr, size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	mgr->large_cnt += 1;
	mgr->allocated_bytes += size;
	update_mgr(mgr, size);
	return (blk + 1);
}

static void *alloc_block(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_slb_blk(mgr, size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	update_mgr(mgr, size);
	return (blk + 1);
}

void    	*malloc(size_t size)
{
	t_mgr	*mgr;
    void    *ret;

    pthread_mutex_lock(&g_mux);
	if (size <= 0)
	{
		pthread_mutex_unlock(&g_mux);
		return(NULL);
	}
	if (!(mgr = get_mgr(FALSE)))
    {
        pthread_mutex_unlock(&g_mux);
        return (NULL);
    }
	ret = size <= SMLSZ ? alloc_block(mgr, size) : alloc_large(mgr, size);
	pthread_mutex_unlock(&g_mux);
    return (ret);
}
