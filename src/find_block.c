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

	slab = mgr->head_slab;
	mgr->s = slab;
	while (slab)
	{
		if (size <= TNYSZ && slab->tiny_avail > 0)
			return (slab);
		else if (size > TNYSZ && size <= SMLSZ && slab->small_avail > 0)
			return (slab);
		mgr->s = slab;
		slab = slab->next;
	}
	slab = create_slab(mgr);
	mgr->s->next = slab;
	return (slab);
}

t_block			*make_lrgblk(t_mgr *mgr, size_t size)
{
	mgr->b = NULL;
	mgr->b = mmap(0, SBLKSZ + size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mgr->b == MAP_FAILED)
		return (NULL);
	init_block(mgr->b);
	return (mgr->b);
}

t_block			*find_slb_blk(t_mgr *mgr, size_t size)
{
	mgr->b = NULL;
	mgr->s = find_slab(mgr, size);
	if (!(mgr->b = check_queue(mgr->s, size)))
	{
		mgr->b = size <= TNYSZ ? mgr->s->tiny : mgr->s->small;
		while (mgr->b)
		{
			if (mgr->b->avail == TRUE)
			{
				if (size <= TNYSZ)
					mgr->b->mgr->tiny_avail -= 1;
				else
					mgr->b->mgr->small_avail -= 1;
				return (mgr->b);
			}
			mgr->b = mgr->b->next;
		}
	}
	return (mgr->b);
}
