/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:30:11 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/09 13:55:44 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

void		init_mgr(t_mgr *mgr)
{
	mgr->large = NULL;
	mgr->head_slab = NULL;
	mgr->large_frees = 0;
	mgr->large_cnt = 0;
	mgr->total_frees = 0;
	mgr->freed_bytes = 0;
	mgr->total_allocs = 0;
	mgr->total_frees = 0;
	mgr->allocated_bytes = 0;
	mgr->requested_bytes = 0;
}

void		init_block(t_block *blk)
{
	blk->next = NULL;
	blk->mgr.lslb = NULL;
	blk->mgr.slb = NULL;
	blk->avail = TRUE;
	blk->data_size = 0;
}

void		init_slab(t_slab *slab)
{
	slab->next = NULL;
	slab->tiny = NULL;
	slab->tiny_que = NULL;
	slab->tiny_avail = BLKCNT;
	slab->small = NULL;
	slab->small_que = NULL;
	slab->small_avail = BLKCNT;
	slab->size = 0;
}

void		init_lslab(t_lslab *slab)
{
	slab->next = NULL;
	slab->large = NULL;
	slab->totbytes = 0;
	slab->availbytes = 0;
	slab->blkcnt = 0;
	slab->blkfree = 0;
}
