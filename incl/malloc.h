/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:25:30 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/05 13:58:34 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/incl/printf.h"
# include <sys/mman.h>

# define TINYSIZE 64
# define SMALLSIZE 512
# define SLABCOUNT 100

typedef struct      s_slab
{
    struct s_slab   *next;
    size_t 			slab_cnt;
	size_t			slab_size;

}                   t_slab;

typedef struct		s_block
{
	struct s_block	*next;
	t_blean			avail;
	size_t			blk_size;
	size_t 			data_size;
	void			*data;
}					t_block;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
void	show_alloc_mem();

#endif MALLOC_H
