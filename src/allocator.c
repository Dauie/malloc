/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:48:05 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/19 19:39:47 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

t_slab *g_slabs = NULL;

void		link_blocks(t_slab *mgr, t_block *group, size_t count, size_t size)
{
	t_block *h;
	t_block *p;

	h = group;
	p = h;
	while (count--)
	{
		init_block(h, size);
		h->data = h + 1;
		h->next = (t_block *)((char *)h->data + size);
		h->mgr = mgr;
		if (count == 0)
			h->next = NULL;
		else
			h = h->next;
		h->prev = p;
	}
}

void		prep_slab(t_slab *slab)
{
	slab->small = (t_block *)(slab + 1);
	slab->small_end = (void *)(((char*)slab->small + 1) + ((SMLSZ + SBLKSZ) * BLKCNT));
	slab->tiny = (t_block *)(((char *)slab->small + 1) + ((SMLSZ + SBLKSZ) * BLKCNT));
	slab->tiny_end = (void *)(((char*)slab->tiny + 1) + ((TNYSZ + SBLKSZ) * BLKCNT));
	link_blocks(slab, slab->small, BLKCNT, SMLSZ);
	link_blocks(slab, slab->tiny, BLKCNT, TNYSZ);
}

t_slab		*create_slab(t_mgr *mgr)
{
	t_slab	*n_slab;
	size_t 	slbsz;

	slbsz = SLBSZ;
	slbsz += slbsz % getpagesize();
	n_slab = mmap(0, slbsz, PROT_READ | PROT_WRITE,
				   MAP_ANON | MAP_PRIVATE, -1, 0);
	if (n_slab == MAP_FAILED)
		return (NULL);
	init_slab(n_slab);
	prep_slab(n_slab);
	if (!mgr->head_slab)
		mgr->head_slab = n_slab;
	mgr->head_slab->slab_cnt += 1;
	mgr->head_slab->allocated_bytes += SLBSZ;
	return (n_slab);
}

t_slab		*get_slabs(t_mgr *mgr, t_blean debug)
{
	if (!g_slabs && !debug)
	{
		g_slabs = create_slab(mgr);
		g_slabs->allocated_bytes = SLBSZ;
	}
	return (g_slabs);
}

