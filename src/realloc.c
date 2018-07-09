/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 18:47:36 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/04 19:27:34 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		*findncopy(void **mem, size_t size, t_mgr **mgr,
							void *(fn(t_mgr *, size_t)))
{
	t_block		*dst;
	t_block		*old;
	size_t		cpysize;

	if (!(dst = fn(*mgr, size)))
		return (*mem);
	old = (t_block *)*mem - 1;
	cpysize = size < old->data_size ? size : old->data_size;
	ft_memcpy(dst, *mem, cpysize);
	pthread_mutex_unlock(&g_mux);
	free(*mem);
	pthread_mutex_lock(&g_mux);
	return (dst);
}

void			*realloc(void *mem, size_t size)
{
	t_mgr		*mgr;
	t_block		*blk;
	void		*ret;

	ret = NULL;
	pthread_mutex_lock(&g_mux);
	if (!(mgr = get_mgr(FALSE)) ||
			(mem > NULL && !is_allocated(mgr, &mem)))
	{
		pthread_mutex_unlock(&g_mux);
		return (ret);
	}
	if (!mem && size > 0)
		ret = size <= SMLSZ ? alloc_block(mgr, size) : alloc_large(mgr, size);
	else
	{
		blk = (t_block *)mem - 1;
		if (blk->avail == FALSE)
			ret = size <= SMLSZ ? findncopy(&mem, size, &mgr, &alloc_block) :
				findncopy(&mem, size, &mgr, &alloc_large);
		else
			ret = NULL;
	}
	pthread_mutex_unlock(&g_mux);
	return (ret);
}
