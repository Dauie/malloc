/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:11:37 by dauie             #+#    #+#             */
/*   Updated: 2018/01/19 10:49:30 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

void 		free(void *ptr)
{
    t_mgr mgr;

    init_mgr(&mgr);
    if (!(mgr.head_slab = get_slabs(&mgr, TRUE)))
        return;
    mgr.b = (t_block*)ptr - 1;
    mgr.b->avail = TRUE;
    mgr.head_slab->freed_bytes += mgr.b->data_size;
    mgr.head_slab->total_frees += 1;
}