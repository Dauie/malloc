/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:30:11 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/19 10:58:27 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/malloc.h"

void		init_mgr(t_mgr *mgr)
{
	mgr->head_slab = NULL;
	mgr->b = NULL;
	mgr->s = NULL;
}

void		init_block(t_block *blk, size_t size)
{
	blk->next = NULL;
	blk->mgr = NULL;
	blk->avail = TRUE;
	blk->blk_size = size;
	blk->data_size = 0;
	blk->data = NULL;
}

void		init_slab(t_slab *slab)
{
	slab->next = NULL;
	slab->slab_cnt = 0;
	slab->tiny = NULL;
	slab->tiny_avail = BLKCNT;
	slab->small = NULL;
	slab->small_avail = BLKCNT;
	slab->large = NULL;
	slab->large_cnt = 0;
	slab->total_frees = 0;
	slab->freed_bytes = 0;
	slab->total_allocs = 0;
	slab->total_frees = 0;
	slab->allocated_bytes = 0;
	slab->requested_bytes = 0;
}
