/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:11:37 by dauie             #+#    #+#             */
/*   Updated: 2018/07/09 14:24:22 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		remove_lrgblk(t_mgr *mgr, t_block **blk)
{
	t_lslab		*head;
	t_lslab		*tail;

	head = mgr->large;
	tail = NULL;
	while (head)
	{
		if (head == (*blk)->mgr.lslb)
		{
			tail->next = head->next;
			break ;
		}
		tail = head;
		head = head->next;
	}
}

static void		free_lrg_blk(t_mgr *mgr, t_block **blk)
{
	(*blk)->mgr.lslb->blkfree += 1;
	mgr->large_frees += 1;
	if ((*blk)->mgr.lslb->blkfree == (*blk)->mgr.lslb->blkcnt)
	{
		if ((*blk)->mgr.lslb == mgr->large)
			mgr->large = mgr->large->next;
		else
			remove_lrgblk(mgr, blk);
		munmap((*blk)->mgr.lslb, (*blk)->mgr.lslb->totbytes);
	}
}

static void		free_slb_blk(t_mgr *mgr, t_block *blk)
{
	if (blk->data_size <= TNYSZ)
	{
		blk->mgr.slb->tiny_avail += 1;
		if (!blk->mgr.slb->tiny_que)
			blk->mgr.slb->tiny_que = blk;
	}
	else
	{
		blk->mgr.slb->small_avail += 1;
		if (!blk->mgr.slb->small_que)
			blk->mgr.slb->small_que = blk;
	}
	clean_allocations(mgr);
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
	t_block		*blk;

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
			free_lrg_blk(mgr, &blk);
		else if (blk->data_size <= SMLSZ)
			free_slb_blk(mgr, blk);
	}
	pthread_mutex_unlock(&g_mux);
}
