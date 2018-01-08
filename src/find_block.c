/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:41:40 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/07 20:21:34 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

t_block *find_smlblk(t_mgr *mgr, size_t size)
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
			mgr->s = create_slab();
	}
	mgr->head_slab->total_allocs+= 1;
	mgr->head_slab->allocated_bytes+= SMLSZ;
	mgr->s->small_avail -= 1;
	while (mgr->b)
	{
		if (mgr->b->avail == TRUE)
			return (mgr->b);
		mgr->b = mgr->b->next;
	}
	return (NULL);
}

t_block *find_tnyblk(t_mgr *mgr, size_t size)
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
			mgr->s = create_slab();
	}
	mgr->head_slab->total_allocs+= 1;
	mgr->head_slab->allocated_bytes+= TNYSZ;
	mgr->s->tiny_avail -= 1;
	while (mgr->b)
	{
		if (mgr->b->avail == TRUE)
			return (mgr->b);
		mgr->b = mgr->b->next;
	}
	return(NULL);
}