/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:56:34 by rlutt             #+#    #+#             */
/*   Updated: 2018/06/16 18:49:55 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		add_large(t_block **nlrg, t_block **lrg_head)
{
	t_block		*head;
	t_block		*tail;

	if (!(*lrg_head))
	{
        *lrg_head = *nlrg;
		return ;
	}
	head = *lrg_head;
	tail = head;
	while (head)
	{
		tail = head;
		head = head->next;
	}
	head = *nlrg;
	head->prev = tail;
	tail->next = head;
}

void			*alloc_large(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = make_lrgblk(size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	mgr->large_cnt += 1;
	mgr->allocated_bytes += (size + SBLKSZ);
	mgr->requested_bytes += size;
	mgr->total_allocs += 1;
	add_large(&blk, &mgr->large);
	return (blk + 1);
}

void			*alloc_block(t_mgr *mgr, size_t size)
{
	t_block		*blk;

	if (!(blk = find_slb_blk(mgr, size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	mgr->requested_bytes += size;
	mgr->total_allocs += 1;
	return (blk + 1);
}

void			*malloc(size_t size)
{
	t_mgr		*mgr;
	void		*ret;

	pthread_mutex_lock(&g_mux);
	if (size <= 0 || !(mgr = get_mgr(FALSE)))
	{
		pthread_mutex_unlock(&g_mux);
		return (NULL);
	}
	ret = size <= SMLSZ ? alloc_block(mgr, size) : alloc_large(mgr, size);
	pthread_mutex_unlock(&g_mux);
	return (ret);
}
