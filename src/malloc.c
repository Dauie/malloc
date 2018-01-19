/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:56:34 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/08 09:46:14 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void update_mgr(t_mgr *mgr, size_t actual, size_t req) {
	mgr->head_slab->allocated_bytes += actual;
	mgr->head_slab->requested_bytes += req;
	mgr->head_slab->total_allocs += 1;
}

static void *alloc_large(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_lrgblk(mgr, size)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	update_mgr(mgr, size + sizeof(t_block), size);
	return (blk->data);
}

static void *alloc_small(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_smlblk(mgr)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	update_mgr(mgr, SMLSZ, size);
	return (blk->data);
}

static void *alloc_tiny(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_tnyblk(mgr)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	update_mgr(mgr, TNYSZ, size);
	return (blk->data);
}

void    	*malloc(size_t size)
{
	t_mgr	mgr;

    // ft_printf("Malloc Called");
	if (size <= 0)
		return(NULL);
	init_mgr(&mgr);
	if (!(mgr.head_slab = get_slabs(&mgr, FALSE)))
		return(NULL);
	if (size < TNYSZ)
		return (alloc_tiny(&mgr, size));
	else if (size < SMLSZ)
		return (alloc_small(&mgr, size));
	return (alloc_large(&mgr, size));
}
