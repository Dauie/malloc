/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:17:53 by rlutt             #+#    #+#             */
/*   Updated: 2018/03/06 19:21:39 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void                range_print(t_slab *head)
{
    t_slab  *slb;
    void    *sml_end;
    void    *tny_end;

    slb = head;
    sml_end = NULL;
    tny_end = NULL;
    if (!slb)
        return;
    while (slb)
    {
        sml_end = (void *)(((char*)slb->small + 1) + ((SMLSZ + SBLKSZ) * BLKCNT));
        tny_end = (void *)(((char*)slb->tiny + 1) + ((TNYSZ + SBLKSZ) * BLKCNT));
        ft_printf("SMALL - %p\n%p - %p\n", slb->small, slb->small, sml_end);
        ft_printf("TINY - %p\n%p - %p\n", slb->tiny, slb->tiny, tny_end);
        slb = slb->next;
    }
}

void	            show_alloc_mem()
{
   	t_mgr	*mgr;
	t_slab	*head;

    mgr = NULL;
    if (!(mgr = get_mgr(TRUE)))
	{
		ft_printf("No memory allocated\n");
		return;
	}
	head = mgr->head_slab;
	mgr->s = mgr->head_slab;
	mgr->b = mgr->head_slab->large;
    range_print(head);
    ft_printf("Total allocations:\t\t%zu\nTotal frees:\t\t\t%zu\nTotal leaks:\t\t\t%zu\n"
					  "Total unfreed bytes:\t\t%zu\nTotal freed bytes:\t\t%zu\n",
			  mgr->total_allocs, mgr->total_frees, mgr->total_allocs - mgr->total_frees,
              mgr->requested_bytes - mgr->freed_bytes, mgr->freed_bytes);
	ft_printf("Total large allocs:\t\t%zu\n", mgr->large_cnt);
	ft_printf("Total large frees:\t\t%zu\n", mgr->large_frees);
	ft_printf("Total memory requested\t\t%zu\n", mgr->requested_bytes);
	ft_printf("Slab count:\t\t\t%zu\n", slab_len(head));
	ft_printf("Memory mapped:\t\t\t%zu\n", mgr->allocated_bytes);
}
