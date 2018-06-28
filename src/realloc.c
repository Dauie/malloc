/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 18:47:36 by rlutt             #+#    #+#             */
/*   Updated: 2018/06/26 10:58:04 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

static void		*findncopy(void **mem, size_t size, t_mgr *mgr,
							void *(fn(t_mgr *, size_t)))
{
	t_block		*dst;

	if (!(dst = fn(mgr, size)))
		return (mem);
	mgr->b = (t_block *)*mem - 1;
	ft_memcpy(dst, *mem, mgr->b->data_size);
	pthread_mutex_unlock(&g_mux);
	free(*mem);
	pthread_mutex_lock(&g_mux);
	return (dst);
}

void			*realloc(void *mem, size_t size)
{
	t_mgr		*mgr;
	void		*ret;

	ret = mem;
	pthread_mutex_lock(&g_mux);
	if (!(mgr = get_mgr(FALSE)) || (mem > NULL && !is_allocated(mgr, &mem)))
	{
		pthread_mutex_unlock(&g_mux);
		return (ret);
	}
	if (!mem)
	{
		ret = size <= SMLSZ ? alloc_block(mgr, size) : alloc_large(mgr, size);
	}
	else
	{
		if (mgr->b->avail == FALSE)
			ret = size <= SMLSZ ? findncopy(&mem, size, mgr, &alloc_block) :
				  findncopy(&mem, size, mgr, &alloc_large);
	}
	pthread_mutex_unlock(&g_mux);
	return (ret);
}
