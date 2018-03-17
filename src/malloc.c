/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:56:34 by rlutt             #+#    #+#             */
/*   Updated: 2018/03/14 14:27:43 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void update_mgr(t_mgr *mgr, size_t req) {
	mgr->requested_bytes += req;
	mgr->total_allocs += 1;
}

static void *alloc_large(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_lrgblk(mgr, size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	mgr->head_slab->large_cnt += 1;
	mgr->allocated_bytes += size;
	update_mgr(mgr, size);
	return (blk->data);
}

static void *alloc_small(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_smlblk(mgr)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	update_mgr(mgr, size);
	return (blk->data);
}

static void *alloc_tiny(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_tnyblk(mgr)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	update_mgr(mgr, size);
	return (blk->data);
}

void    	*malloc(size_t size)
{
	t_mgr	*mgr;

    mgr = NULL;
	if (size <= 0)
		return(NULL);
	if (!(mgr = get_mgr(FALSE)))
		return(NULL);
	if (size <= TNYSZ)
		return (alloc_tiny(mgr, size));
	else if (size <= SMLSZ)
		return (alloc_small(mgr, size));
	return (alloc_large(mgr, size));
}
