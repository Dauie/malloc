/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dauie <dauie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:13:02 by dauie             #+#    #+#             */
/*   Updated: 2018/06/26 10:58:04 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/malloc.h"

void		*calloc(size_t count, size_t size)
{
	void *ret;

	if (!(ret = malloc(count * size)))
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}
