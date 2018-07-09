/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 19:23:42 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/09 13:54:39 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

void		clean_allocations(t_mgr *mgr)
{
	t_slab *head;
	t_slab *tail;

	head = mgr->head_slab;
	tail = NULL;
	while (head)
	{
		if (head->small_avail == BLKCNT && head->tiny_avail == BLKCNT)
		{
			if (tail)
				tail->next = head->next;
			munmap(head, head->size);
			head = mgr->head_slab;
		}
		else
		{
			tail = head;
			head = head->next;
		}
	}
}
