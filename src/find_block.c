/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:41:40 by rlutt             #+#    #+#             */
/*   Updated: 2018/03/20 12:04:03 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

t_slab	*find_slab(t_mgr *mgr, size_t size)
{
	t_slab *slab;

	slab = mgr->head_slab;
	mgr->s = slab;
	while (slab)
	{
		if (size <= TNYSZ && slab->tiny_avail == 0)
			convert_to_tiny(slab);
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

t_block *find_lrgblk(t_mgr *mgr, size_t size)
{
	t_block		*p;

	p = NULL;
	mgr->b = mgr->head_slab->large;
	while (mgr->b)
	{
		if (mgr->b->data_size >= size && mgr->b->avail)
			return (mgr->b);
		p = mgr->b;
		mgr->b = mgr->b->next;
	}
	mgr->b = mmap(0, size + SBLKSZ, PROT_READ | PROT_WRITE,
				  MAP_ANON | MAP_PRIVATE | MAP_NOCACHE, -1, 0);
	if (mgr->b == MAP_FAILED)
		return (NULL);
	init_block(mgr->b);
	if (p)
		p->next = mgr->b;
	return(mgr->b);
}

t_block *find_slb_blk(t_mgr *mgr, size_t size)
{
	mgr->b = NULL;
	mgr->s = find_slab(mgr, size);
	if (!(mgr->b = check_queue(mgr->s, size)))
	{
		if (size <= TNYSZ)
			mgr->b = mgr->s->tiny;
		else
			mgr->b = mgr->s->small;
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

