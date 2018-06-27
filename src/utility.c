/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 18:51:08 by rlutt             #+#    #+#             */
/*   Updated: 2018/06/26 10:58:04 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"


t_blean is_allocated(t_mgr *mgr, void **ptr)
{
	t_block *lrg;
	t_slab 	*slb;

	slb = mgr->head_slab;
	while (slb)
	{
		if (*ptr >= (void *)slb && *ptr <= (void *)((char *)slb + SLBSZ))
			return (TRUE);
		lrg = slb->large;
		while (lrg)
		{
			if (*ptr >= (void *)lrg && *ptr <= (void *)((char *)lrg + lrg->data_size))
				return (TRUE);
			lrg = lrg->next;
		}
		slb = slb->next;
	}
	return (FALSE);
}

int		slab_len(t_slab *list)
{
	int	i;

	i = 0;
	while (list && ++i)
		list = list->next;
	return (i);
}


