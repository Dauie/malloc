/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:48:05 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/07 18:41:08 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

t_slab *g_slabs = NULL;

void		link_blocks(t_block *group, size_t count, size_t size)
{
	t_block *p;

	p = group;
	while (count--)
	{
		init_block(p, size);
		p->data = p + 1;
		p->next = (t_block *)((char *)p->data + size);
		if (count == 0)
			p->next = NULL;
		else
			p = p->next;
	}
}

void		prep_slab(t_slab *slab)
{
	slab->small = (t_block *)(slab + 1);
	slab->tiny = (t_block *)((char *)slab->small + ((SMLSZ + sizeof(t_block)) * BLKCNT));
	link_blocks(slab->small, BLKCNT, SMLSZ);
	link_blocks(slab->tiny, BLKCNT, TNYSZ);
}

t_slab		*create_slab(t_mgr *mgr)
{
	t_slab	*n_slab;

	n_slab = mmap(0, SLBSZ, PROT_READ | PROT_WRITE,
				   MAP_ANON | MAP_PRIVATE, -1, 0);
	if (n_slab == MAP_FAILED)
		return (NULL);
	init_slab(n_slab);
	prep_slab(n_slab);
	if (!mgr->head_slab)
		mgr->head_slab = n_slab;
	mgr->head_slab->allocated_bytes += SLBSZ;
	return (n_slab);
}

t_slab		*get_slabs(t_mgr *mgr, t_blean debug)
{
	if (!g_slabs && !debug)
	{
		g_slabs = create_slab(mgr);
		g_slabs->slab_cnt = 1;
		g_slabs->allocated_bytes = SLBSZ;
	}
	return (g_slabs);
}

