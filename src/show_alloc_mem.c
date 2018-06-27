/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:17:53 by rlutt             #+#    #+#             */
/*   Updated: 2018/06/26 10:58:04 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		range_print(t_slab *head)
{
	t_slab		*slb;
	void		*sml_end;
	void		*tny_end;

	slb = head;
	if (!slb)
		return ;
	while (slb)
	{
		sml_end = (void *)(((char*)slb->small + sizeof(t_block)) +
				((SMLSZ + SBLKSZ) * BLKCNT));
		tny_end = (void *)(((char*)slb->tiny + sizeof(t_block)) +
				((TNYSZ + SBLKSZ) * BLKCNT));
		ft_printf("SMALL - %p\n%p - %p\n", slb->small, slb->small, sml_end);
		ft_printf("TINY - %p\n%p - %p\n", slb->tiny, slb->tiny, tny_end);
		slb = slb->next;
	}
}

void			show_alloc_mem(void)
{
	t_mgr		*m;
	t_slab		*head;

	if (!(m = get_mgr(TRUE)))
	{
		ft_printf("No memory allocated\n");
		return ;
	}
	head = m->head_slab;
	m->s = m->head_slab;
	m->b = m->head_slab->large;
	range_print(head);
	ft_printf("Total allocations:\t\t%zu\n"
			"Total frees:\t\t\t%zu\nTotal leaks:\t\t\t%zu\n"
			"Total unfreed bytes:\t\t%zu\nTotal freed bytes:\t\t%zu\n",
			m->total_allocs, m->total_frees, m->total_allocs - m->total_frees,
			m->requested_bytes - m->freed_bytes, m->freed_bytes);
	ft_printf("Total large allocs:\t\t%zu\n", m->large_cnt);
	ft_printf("Total large frees:\t\t%zu\n", m->large_frees);
	ft_printf("Total memory requested\t\t%zu\n", m->requested_bytes);
	ft_printf("Slab count:\t\t\t%d\n", slab_len(head));
	ft_printf("Memory mapped:\t\t\t%zu\n", m->allocated_bytes);
}
