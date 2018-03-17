/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:11:37 by dauie             #+#    #+#             */
/*   Updated: 2018/03/14 14:46:50 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

// you gotta munmap the large bits.

static void	free_lrg_blk(t_mgr *mgr, t_block *ptr)
{
	if (ptr->prev && ptr->prev->next)
		ptr->prev->next = ptr->next;
	if (ptr->next && ptr->next->prev)
		ptr->next->prev = ptr->prev;
	munmap(ptr, ptr->data_size);
	mgr->large_frees += 1;
}


void 		free(void *ptr)
{
    t_mgr *mgr;

    mgr = NULL;
    if (!ptr || !(mgr = get_mgr(TRUE)))
        return;
    mgr->b = (t_block*)ptr - 1;
	if (mgr->b->avail == FALSE) {
		mgr->b->avail = TRUE;
		mgr->freed_bytes += mgr->b->data_size;
		mgr->total_frees += 1;
		if (mgr->b->data_size > SMLSZ)
			free_lrg_blk(mgr, mgr->b);
		else if (mgr->b->data_size <= SMLSZ && mgr->b->data_size > TNYSZ)
		{
			mgr->b->mgr->small_avail += 1;
			if (!mgr->b->mgr->small_que)
				mgr->b->mgr->small_que = mgr->b;
		}
		else if (mgr->b->data_size <= TNYSZ)
		{
			mgr->b->mgr->tiny_avail += 1;
			if (!mgr->b->mgr->tiny_que)
				mgr->b->mgr->tiny_que = mgr->b;
		}
	}
}