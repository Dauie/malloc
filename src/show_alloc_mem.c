/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:17:53 by rlutt             #+#    #+#             */
/*   Updated: 2018/06/16 15:31:20 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		print_large_blocks(t_block **large)
{
	t_block		*blk;
	void		*data_start;
	void		*data_end;

	blk = *large;
	while (blk)
	{
		if (blk->avail == FALSE)
		{
			data_start = (void *)(blk + 1);
			data_end = (void *)((char*)(blk + 1) + blk->data_size);
			ft_printf("LARGE : %p\n%p - %p : %zu\n", blk, data_start,
					data_end, blk->data_size);
		}
		blk = blk->next;
	}
}

static void		print_slab_blocks(t_block *blk)
{
	while (blk)
	{
		if (blk->avail == FALSE)
			ft_printf("%p - %p : %zu\n", blk + 1,
					(char*)(blk + 1) + blk->data_size, blk->data_size);
		blk = blk->next;
	}
}

static void		range_print(t_mgr *mgr, t_slab *head)
{
	t_slab		*slb;
	void		*sml_end;
	void		*tny_end;

	slb = head;
	if (!slb)
		return ;
	while (slb)
	{
		sml_end = (void *)((char*)slb->small + SMLSEC);
		tny_end = (void *)((char*)slb->tiny + TNYSEC);
		ft_printf("SMALL : %p\n%p - %p\n", slb->small, slb->small, sml_end);
		print_slab_blocks(slb->small);
		ft_printf("TINY : %p\n%p - %p\n", slb->tiny, slb->tiny, tny_end);
		print_slab_blocks(slb->tiny);
		slb = slb->next;
	}
	print_large_blocks(&mgr->large);
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
	range_print(m, head);
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
