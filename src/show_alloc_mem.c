/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:17:53 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/19 14:43:11 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

void	            show_alloc_mem()
{
   	t_mgr	mgr;
	t_slab	*head;

	init_mgr(&mgr);
    if (!(mgr.head_slab = get_slabs(&mgr, TRUE)))
	{
		ft_printf("No memory allocated\n");
		return;
	}
	head = mgr.head_slab;
	ft_printf("HEAD - %p\n", head);
	ft_printf("SMALL - %p\n%p - %p\n", head->small, head->small, head->small_end);
	ft_printf("TINY - %p\n%p - %p\n", head->tiny, head->tiny, head->tiny_end);
    ft_printf("Total allocations:\t\t%zu\nTotal frees:\t\t\t%zu\nTotal leaks:\t\t\t%zu\nTotal unfreed bytes:\t\t%zu\nTotal freed bytes:\t\t%zu\n",
			  head->total_allocs, head->total_frees, head->total_allocs - head->total_frees,
              head->requested_bytes - head->freed_bytes, head->freed_bytes);
	ft_printf("Total large allocs:\t\t%zu\n", head->large_cnt);
	ft_printf("Total large frees:\t\t%zu\n", head->large_frees);
	ft_printf("Total memory requested\t\t%zu\n", head->requested_bytes);
	ft_printf("Slab count:\t\t\t%zu\n", head->slab_cnt);
	ft_printf("Memory mapped:\t\t\t%zu\n", head->allocated_bytes);
}