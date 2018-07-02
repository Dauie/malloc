/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:11:37 by dauie             #+#    #+#             */
/*   Updated: 2018/06/16 15:30:18 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		free_lrg_blk(t_mgr *mgr, t_block *blk)
{
	if (!mgr->large || !blk)
		return ;
	if (mgr->large == blk)
		mgr->large = blk->next;
	if (blk->next)
        blk->next->prev = blk->prev;
	if (blk->prev)
        blk->prev->next = blk->next;
	munmap(blk, blk->data_size);
	mgr->large_frees += 1;
}

static void		free_slb_blk(t_block *blk)
{
    if (blk->data_size <= SMLSZ)
    {
        blk->mgr->small_avail += 1;
        if (!blk->mgr->small_que)
            blk->mgr->small_que = blk;
    }
    else
    {
        blk->mgr->tiny_avail += 1;
        if (!blk->mgr->tiny_que)
            blk->mgr->tiny_que = blk;
    }
}

static void		update_block(t_mgr *mgr, t_block *blk)
{
    blk->avail = TRUE;
	mgr->freed_bytes += blk->data_size;
	mgr->total_frees += 1;
}

void			free(void *ptr)
{
	t_mgr		*mgr;
    t_block     *blk;

	mgr = NULL;
	pthread_mutex_lock(&g_mux);
	if (!ptr || !(mgr = get_mgr(TRUE)) || !is_allocated(mgr, &ptr))
	{
		pthread_mutex_unlock(&g_mux);
		return ;
	}
    blk = (t_block*)ptr - 1;
	if (blk->avail == FALSE)
	{
		update_block(mgr, blk);
		if (blk->data_size > SMLSZ)
			free_lrg_blk(mgr, blk);
		else if (blk->data_size <= SMLSZ)
			free_slb_blk(blk);
        clean_allocations(mgr);
	}
	pthread_mutex_unlock(&g_mux);
}
