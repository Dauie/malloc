/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:56:34 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/08 15:43:34 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

//static void		add_large(t_block **nlrg, t_block **lrg, t_block **lrg_end)
//{
//	if (!(*lrg))
//	{
//		*lrg = *nlrg;
//		*lrg_end = *lrg;
//		return ;
//	}
//	(*lrg_end)->next = *nlrg;
//	(*lrg_end) = (*lrg_end)->next;
//}

t_block			*get_block(t_lslab **slb, size_t size, t_blean *new)
{
	t_block		*blk;
	t_block		*tail;

	if (!(*slb)->large)
	{
		blk = (t_block *)((*slb) + 1);
		(*slb)->large = blk;
		*new = TRUE;
	}
	else
	{
		blk = (*slb)->large;
		tail = NULL;
		while (blk)
		{
			if (blk->avail == TRUE && blk->data_size >= size)
				return (blk);
			tail = blk;
			blk = blk->next;
		}
		blk = (t_block *)((char *)tail + (SBLKSZ + tail->data_size));
		tail->next = blk;
		*new = TRUE;
	}
	return (blk);
}

// make function to place blocks in large section.
t_lslab			*find_lrgslb(t_mgr *mgr, size_t size)
{
	t_lslab		*slb;
	t_lslab		*tail;


	if (!mgr->large)
		mgr->large = make_lrgslb(mgr, size);
	slb = mgr->large;
	tail = slb;
	while (slb)
	{
		if (slb->availbytes > size + SBLKSZ)
			break;
		tail = slb;
		slb = slb->next;
	}
	if (!slb)
	{
		tail->next = make_lrgslb(mgr, size);
		return (tail->next);
	}
	return (slb);
}

void			*alloc_large(t_mgr *mgr, size_t size)
{
	t_lslab		*slb;
	t_block		*blk;
	t_blean		new;

	new = FALSE;
	if (!(slb = find_lrgslb(mgr, size)))
		return (NULL);
	if (!(blk = get_block(&slb, size, &new)))
		return (NULL);
	init_block(blk);
	if (new == TRUE)
	{
		slb->availbytes -= (size + SBLKSZ);
		slb->blkcnt += 1;
	}
	blk->avail = FALSE;
	blk->data_size = size;
	blk->mgr.lslb = slb;
	/* TODO: May need altering */
	mgr->requested_bytes += size;
	mgr->total_allocs += 1;
	mgr->large_cnt += 1;
	return (blk + 1);
}

void			*alloc_block(t_mgr *mgr, size_t size)
{
	t_block		*blk;

	if (!(blk = find_slb_blk(mgr, size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	mgr->requested_bytes += size;
	mgr->total_allocs += 1;
	return (blk + 1);
}

void			*malloc(size_t size)
{
	t_mgr		*mgr;
	void		*ret;

	pthread_mutex_lock(&g_mux);
	if (size <= 0 || !(mgr = get_mgr(FALSE)))
	{
		pthread_mutex_unlock(&g_mux);
		return (NULL);
	}
	ret = size <= SMLSZ ? alloc_block(mgr, size) : alloc_large(mgr, size);
	pthread_mutex_unlock(&g_mux);
	return (ret);
}
