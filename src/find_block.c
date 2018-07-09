/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 12:53:50 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/08 13:23:42 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static t_block			*make_slb_blk(t_slab **mgr, t_block **lst_blk, size_t blk_size)
{
	t_block *blk;

	blk = *lst_blk;
	blk->next = (t_block *)((char *)*lst_blk + (blk_size + SBLKSZ));
	init_block(blk->next);
	blk->next->mgr.slb = *mgr;
	return (blk->next);
}

	static t_block	*check_queue(t_slab **mgr, t_block **section, t_block **que, size_t blksz)
{
	t_block		*p;
	long		gap;
	size_t		*tick;

	gap = (t_block *)((char *)*section + ((SBLKSZ + blksz) * (BLKCNT - 1))) - *section;
	p = *que;
	if (*que && (*que)->next == NULL && (*que - *section) <= gap)
	{
		(*que)->next = make_slb_blk(mgr, que, blksz <= TNYSZ ? TNYSZ : SMLSZ);
		*que = (*que)->next;
	}
	if (p)
	{
		tick = blksz <= TNYSZ ?  &(*mgr)->tiny_avail : &(*mgr)->small_avail;
		*tick -= 1;
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
	t_slab		*prev;

	slab = mgr->head_slab;
	prev = NULL;
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
	if (prev)
		prev->next = slab;
	return (slab);
}


t_block			*find_slb_blk(t_mgr *mgr, size_t size)
{
	t_block		*blk;
	t_slab		*slb;

	blk = NULL;
	slb = mgr->head_slab ? find_slab(mgr, size) : create_slab(mgr);
	{
		if ((blk = check_queue(&slb, (size <= TNYSZ ? &slb->tiny : &slb->small),
							(size <= TNYSZ ? &slb->tiny_que : &slb->small_que), size <= TNYSZ ? TNYSZ : SMLSZ)))
			return(blk);
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
			if (blk->next == NULL)
				make_slb_blk(&slb, &blk, size <= TNYSZ ? TNYSZ : SMLSZ);
			blk = blk->next;
		}
	}
	return (blk);
}
