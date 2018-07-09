/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:41:40 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/08 17:47:35 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static t_block	*check_queue(t_slab *slb, size_t blksz)
{
	t_block		*p;

	p = NULL;
	if (blksz > TNYSZ && blksz <= SMLSZ && slb->small_que)
	{
		p = slb->small_que;
		slb->small_avail -= 1;
		if (p->next && p->next->avail == TRUE)
			slb->small_que = p->next;
		else
			slb->small_que = NULL;
	}
	else if (blksz <= TNYSZ && slb->tiny_que)
	{
		p = slb->tiny_que;
		slb->tiny_avail -= 1;
		if (p->next && p->next->avail == TRUE)
			slb->tiny_que = p->next;
		else
			slb->tiny_que = NULL;
	}
	return (p);
}

t_lslab			*make_lrgslb(t_mgr *mgr, size_t size)
{
	t_lslab		*slb;
	int			pgsz;

	pgsz = getpagesize();
	size += SLSLBSZ;
	size += (pgsz - size % pgsz);
	slb = mmap(0, size, PROT_READ | PROT_WRITE,
			   MAP_ANON | MAP_PRIVATE, -1, 0);
	if (slb == MAP_FAILED)
		return (NULL);
	init_lslab(slb);
	slb->totbytes = size;
	slb->availbytes = size - SLSLBSZ;
	mgr->allocated_bytes += size;
	return (slb);
}


static t_slab	*find_slab(t_mgr *mgr, size_t size)
{
	t_slab		*slab;
    t_slab      *prev;

	slab = mgr->head_slab;
	prev = slab;
	while (slab)
	{
		if (size <= TNYSZ && slab->tiny_avail > 0)
			return (slab);
		else if (size > TNYSZ && size <= SMLSZ && slab->small_avail > 0)
			return (slab);
		prev = slab;
		slab = slab->next;
	}
	slab = create_slab(mgr);
	prev->next = slab;
	return (slab);
}


t_block			*find_slb_blk(t_mgr *mgr, size_t size)
{
    t_block     *blk;
    t_slab      *slb;

	slb = mgr->head_slab ? find_slab(mgr, size) : create_slab(mgr);
	if (!(blk = check_queue(slb, size)))
	{
        blk = size <= TNYSZ ? slb->tiny : slb->small;
		while (blk)
		{
			if (blk->avail == TRUE)
			{
				if (size <= TNYSZ)
                    blk->mgr.slb->tiny_avail -= 1;
				else
                    blk->mgr.slb->small_avail -= 1;
				return (blk);
			}
            blk = blk->next;
		}
	}
	return (blk);
}
