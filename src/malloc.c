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

//static void *alloc_large(t_mgr *mgr, size_t size)
//{
//
//}

static void *alloc_small(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_smlblk(mgr)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	mgr->head_slab->allocated_bytes+= SMLSZ;
	return (blk->data);
}

static void *alloc_tiny(t_mgr *mgr, size_t size)
{
	t_block	*blk;

	if (!(blk = find_tnyblk(mgr)))
		return (NULL);
	blk->avail = FALSE;
	blk->data_size = size;
	return (blk->data);
}

void    	*malloc(size_t size)
{
	t_mgr	mgr;

	if (size <= 0)
		return(NULL);
	init_mgr(&mgr);
	if (!(mgr.head_slab = get_slabs()))
		return(NULL);
	if (size < TNYSZ)
		return (alloc_tiny(&mgr, size));
	else if (size < SMLSZ)
		return (alloc_small(&mgr, size));
	return (NULL);
//	return (alloc_large(&mgr));
}
