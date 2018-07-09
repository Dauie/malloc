/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 18:51:08 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/08 17:35:18 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static t_blean		alloced_in_tiny(void **secstart, void **ptr)
{
	if (*ptr == (t_block*)secstart + 1)
		return (TRUE);
	else if ((*ptr - *secstart) % 64 == 32)
		return (TRUE);
	return (FALSE);
}

static t_blean		alloced_in_small(void **secstart, void **ptr)
{
	if (*ptr == (t_block*)secstart + 1)
		return (TRUE);
	else if ((*ptr - *secstart) % 512 == 32)
		return (TRUE);
	return (FALSE);
}

t_blean				is_allocated(t_mgr *mgr, void **ptr)
{
	t_lslab			*lslab;
	t_block			*lrg;
	t_slab			*slb;

	slb = mgr->head_slab;
	while (slb)
	{
		if (*ptr >= (void *)slb->small &&
				*ptr <= (void *)((char *)slb->tiny - 1))
			return (alloced_in_small((void*)&slb->small, ptr));
		else if (*ptr >= (void *)slb->tiny &&
				*ptr <= (void *)((char *)slb->tiny + TNYSEC))
			return (alloced_in_tiny((void*)&slb->tiny, ptr));
		slb = slb->next;
	}
	lslab = mgr->large;
	while (lslab)
	{
		lrg = lslab->large;
		while (lrg)
		{
			if (*ptr == (void *)(lrg + 1))
				return (TRUE);
			lrg = lrg->next;
		}
		lslab = lslab->next;
	}
	return (FALSE);
}

int					slab_len(t_slab *list)
{
	int				i;

	i = 0;
	while (list && ++i)
		list = list->next;
	return (i);
}
