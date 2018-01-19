/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:41:40 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/19 14:44:16 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

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
	mgr->s = mgr->head_slab;
	while (mgr->b == NULL)
	{
		while (mgr->s)
		{
			if (mgr->s->small_avail > 0)
			{
				mgr->b = mgr->s->small;
				break;
			}
			mgr->s = mgr->s->next;
		}
		if (mgr->s == NULL)
			mgr->s = create_slab(mgr);
	}
	mgr->s->small_avail -= 1;
	while (mgr->b)
	{
		if (mgr->b->avail == TRUE)
			return (mgr->b);
		mgr->b = mgr->b->next;
	}
	return (NULL);
}

t_block *find_tnyblk(t_mgr *mgr)
{
	mgr->s = mgr->head_slab;
	while (mgr->b == NULL)
	{
		while (mgr->s)
		{
			if (mgr->s->tiny_avail > 0)
			{
				mgr->b = mgr->s->tiny;
				break;
			}
			mgr->s = mgr->s->next;
		}
		if (mgr->s == NULL)
			mgr->s = create_slab(mgr);
	}
	mgr->s->tiny_avail -= 1;
	while (mgr->b)
	{
		if (mgr->b->avail == TRUE)
			return (mgr->b);
		mgr->b = mgr->b->next;
	}
	return(NULL);
}
