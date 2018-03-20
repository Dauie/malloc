/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:48:05 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/20 18:50:57 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

t_mgr	*g_mgr = NULL;
pthread_mutex_t g_mux = PTHREAD_MUTEX_INITIALIZER;

void		    link_blocks(t_slab *slb, t_block *group, size_t count, size_t size)
{
	t_block     *h;
	t_block     *p;

	h = group;
	p = NULL;
	while (count--)
	{
		init_block(h);
		h->next = (t_block *)((char *)h + (size + sizeof(t_block)));
		h->mgr = slb;
		if (count == 0)
			h->next = NULL;
		else
			h = h->next;
		h->prev = p;
		p = h;
	}
}

void		prep_slab(t_slab *slab)
{
	slab->small = (t_block *)(slab + 1);
	slab->small_que = slab->small;
	slab->tiny = (t_block *)(((char *)slab->small + 1) + ((SMLSZ + SBLKSZ) * BLKCNT));
	slab->tiny_que = slab->tiny;
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
				   MAP_ANON | MAP_PRIVATE | MAP_NOCACHE , -1, 0);
	if (n_slab == MAP_FAILED)
		return (NULL);
	init_slab(n_slab);
	prep_slab(n_slab);
	if (!mgr->head_slab)
		mgr->head_slab = n_slab;
	mgr->allocated_bytes += SLBSZ;
	return (n_slab);
}

t_mgr		*get_mgr(t_blean debug)
{
	if (!g_mgr && !debug)
	{
        g_mgr = mmap(0, sizeof(t_mgr), PROT_READ | PROT_WRITE,
                     MAP_ANON | MAP_PRIVATE | MAP_NOCACHE, -1, 0);
        if (g_mgr == MAP_FAILED)
            return (NULL);
        init_mgr(g_mgr);
		g_mgr->head_slab = create_slab(g_mgr);
	}
	return (g_mgr);
}
