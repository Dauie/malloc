/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:11:37 by dauie             #+#    #+#             */
/*   Updated: 2018/01/20 19:32:12 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

// you gotta munmap the large bits.

static void	free_lrg_blk(t_mgr *mgr, t_block *ptr)
{
	if (ptr->prev && ptr->prev->next)
		ptr->prev->next = ptr->next;
	if (ptr->next && ptr->next->prev)
		ptr->next->prev = ptr->prev;
	munmap(ptr, ptr->blk_size);
	mgr->head_slab->large_frees += 1;
}


void 		free(void *ptr)
{
    t_mgr mgr;

    init_mgr(&mgr);
    if (!ptr || !(mgr.head_slab = get_slabs(&mgr, TRUE)))
        return;
    mgr.b = (t_block*)ptr - 1;
    mgr.b->avail = TRUE;
    mgr.head_slab->freed_bytes += mgr.b->data_size;
    mgr.head_slab->total_frees += 1;
	if (mgr.b->blk_size > SMLSZ)
		free_lrg_blk(&mgr, mgr.b);
	else if (mgr.b->blk_size == SMLSZ)
	{
		mgr.b->mgr->small_avail += 1;
		if (!mgr.b->mgr->small_que)
			mgr.b->mgr->small_que = mgr.b;
	}
	else if (mgr.b->blk_size == TNYSZ)
	{
		mgr.b->mgr->tiny_avail += 1;
		if (!mgr.b->mgr->tiny_que)
			mgr.b->mgr->tiny_que = mgr.b;
	}
}