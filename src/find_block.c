/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:41:40 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/20 18:01:20 by dauie            ###   ########.fr       */
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
		if (size == TNYSZ)
			convert_to_tiny(slab);
		if (size == SMLSZ && slab->small_avail > 0)
			return (slab);
		else if (size == TNYSZ && slab->tiny_avail > 0)
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
				  MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mgr->b == MAP_FAILED)
		return (NULL);
	init_block(mgr->b, size);
	mgr->b->data = mgr->b + 1;
	if (p)
		p->next = mgr->b;
	mgr->head_slab->large_cnt += 1;
	mgr->head_slab->allocated_bytes += size;
	return(mgr->b);
}

t_block *find_smlblk(t_mgr *mgr)
{
	mgr->b = NULL;

	mgr->s = find_slab(mgr, SMLSZ);
	if (!(mgr->b = check_queue(mgr->s, SMLSZ)))
	{
		mgr->b = mgr->s->small;
		while (mgr->b)
		{
			if (mgr->b->avail == TRUE)
			{
				mgr->b->mgr->small_avail -= 1;
				return (mgr->b);
			}
			mgr->b = mgr->b->next;
		}
	}
	return (mgr->b);
}

t_block *find_tnyblk(t_mgr *mgr)
{
	mgr->b = NULL;

	mgr->s = find_slab(mgr, TNYSZ);
	if (!(mgr->b = check_queue(mgr->s, TNYSZ)))
	{
		mgr->b = mgr->s->tiny;
		while (mgr->b)
		{
			if (mgr->b->avail == TRUE)
			{
				mgr->b->mgr->tiny_avail -= 1;
				return (mgr->b);
			}
			mgr->b = mgr->b->next;
		}
	}
	return (mgr->b);
}

