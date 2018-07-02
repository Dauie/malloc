/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:41:40 by rlutt             #+#    #+#             */
/*   Updated: 2018/06/16 15:30:39 by rlutt            ###   ########.fr       */
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

t_block			*make_lrgblk(size_t size)
{
    t_block     *blk;

	blk = mmap(0, SBLKSZ + size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (blk == MAP_FAILED)
		return (NULL);
	init_block(blk);
	return (blk);
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
                    blk->mgr->tiny_avail -= 1;
				else
                    blk->mgr->small_avail -= 1;
				return (blk);
			}
            blk = blk->next;
		}
	}
	return (blk);
}
