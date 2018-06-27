/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:11:37 by dauie             #+#    #+#             */
/*   Updated: 2018/06/26 10:58:04 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		free_lrg_blk(t_mgr *mgr, t_block *ptr)
{
	if (ptr->prev && ptr->prev->next)
		ptr->prev->next = ptr->next;
	if (ptr->next && ptr->next->prev)
		ptr->next->prev = ptr->prev;
	munmap(ptr, ptr->data_size);
	mgr->large_frees += 1;
}

static void		free_sml_blk(t_mgr *mgr, t_block *ptr)
{
	ptr->mgr->small_avail += 1;
	if (!ptr->mgr->small_que)
		ptr->mgr->small_que = mgr->b;
}

static void		free_tny_blk(t_mgr *mgr, t_block *ptr)
{
	ptr->mgr->tiny_avail += 1;
	if (!ptr->mgr->tiny_que)
		ptr->mgr->tiny_que = mgr->b;
}

static void		update_block(t_mgr *mgr)
{
	mgr->b->avail = TRUE;
	mgr->freed_bytes += mgr->b->data_size;
	mgr->total_frees += 1;
}

void			free(void *ptr)
{
	t_mgr		*mgr;

	mgr = NULL;
	pthread_mutex_lock(&g_mux);
	if (!ptr || !(mgr = get_mgr(TRUE)) || !is_allocated(mgr, &ptr))
	{
		pthread_mutex_unlock(&g_mux);
		return ;
	}
	mgr->b = (t_block*)ptr - 1;
	if (mgr->b->avail == FALSE)
	{
		update_block(mgr);
		if (mgr->b->data_size > SMLSZ)
			free_lrg_blk(mgr, mgr->b);
		else if (mgr->b->data_size <= SMLSZ && mgr->b->data_size > TNYSZ)
			free_sml_blk(mgr, mgr->b);
		else if (mgr->b->data_size <= TNYSZ)
			free_tny_blk(mgr, mgr->b);
	}
	pthread_mutex_unlock(&g_mux);
}
