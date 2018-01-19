/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:25:30 by rlutt             #+#    #+#             */
/*   Updated: 2018/01/19 15:13:46 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/incl/printf.h"
# include <sys/mman.h>

/**
 * 							SLAB DESIGN
 * Each slab will be a total of 93224 bytes (22.76 pages on the average OS)
 * Each slab will be divided into 'tiny' and 'medium' sections
 * the tiny sections will be 64 bytes totaling 8192 bytes, medium will be
 * 512 totaling 65536 bytes, adding to the grand 73,728.
 * tiny sections will start at the end of the memory space, and medium
 * at the begining.
 * block splitting will be implemented to reclaim memory
 * from the medium section and grant it to the tiny if possible
 *
 * All large allocations will only reside in the head slab node.
 *
 * */

/**
 * 							NAMING EXPLAINATION
 * TNYSZ:	Size of user space in a tiny block
 * SMLSZ:	Size of user space in a small block
 * BLKCNT:	Amount of blocks for each size
 * SBLKSZ:	Size of the t_block struct
 * SSLBSZ:	Size of the t_slab struct
 * SLBSZ:	Size of an entire 'slab'
 *
 * */

# define TNYSZ 64
# define SMLSZ 256
# define BLKCNT 200
# define SBLKSZ sizeof(t_block)
# define SSLBSZ sizeof(t_slab)
# define SLBSZ (SSLBSZ + (((SBLKSZ + TNYSZ) * BLKCNT) + ((SBLKSZ + SMLSZ) * BLKCNT)))


typedef struct      s_slab
{
    struct s_slab   *next;
	size_t 			slab_cnt;
	struct s_block			*tiny;
	void			*tiny_end;
	size_t			tiny_avail;
	struct s_block			*small;
	void			*small_end;
	size_t			small_avail;
	struct s_block		*large;
	size_t			large_cnt;
	size_t			total_frees;
	size_t			freed_bytes;
	size_t			total_allocs;
	size_t			allocated_bytes;
	size_t 			requested_bytes;
}                   t_slab;

typedef struct		s_block
{
	struct s_block	*next;
	struct s_slab   *mgr;
	t_blean			avail;
	size_t			blk_size;
	size_t 			data_size;
	void			*data;
}					t_block;

typedef struct		s_mgr
{
	t_slab			*head_slab;
	t_block			*b;
	t_slab			*s;
}					t_mgr;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
void	show_alloc_mem(void);
t_slab	*get_slabs(t_mgr *mgr, t_blean debug);
void	init_mgr(t_mgr *mgr);
void	init_slab(t_slab *slab);
void	init_block(t_block *blk, size_t size);
t_slab	*create_slab(t_mgr *mgr);
t_block *find_smlblk(t_mgr *mgr);
t_block *find_tnyblk(t_mgr *mgr);
t_block *find_lrgblk(t_mgr *mgr, size_t size);

#endif
