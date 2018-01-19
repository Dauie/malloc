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
	t_block	blk;

	p = group;
	init_block(&blk, size);
	while (count--)
	{
		ft_memcpy(p, (const void *)&blk, sizeof(t_block));
		p->data = p + 1;
		p->data_size = count;
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

t_slab		*create_slab(void)
{
	t_slab	*n_slab;
	t_slab	copy;

	init_slab(&copy);
	n_slab = mmap(0, SLBSZ, PROT_READ | PROT_WRITE,
				   MAP_ANON | MAP_PRIVATE, -1, 0);
	if (n_slab == MAP_FAILED)
		return (NULL);
	ft_memcpy(n_slab, (const void *)&copy, sizeof(t_slab));
	prep_slab(n_slab);
	return (n_slab);
}

t_slab		*get_slabs(void)
{
	if (!g_slabs)
	{
		g_slabs = create_slab();
		g_slabs->slab_cnt = 1;
		g_slabs->allocated_bytes = SLBSZ;
	}
	return (g_slabs);
}

