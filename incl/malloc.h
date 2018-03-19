/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:25:30 by rlutt             #+#    #+#             */
/*   Updated: 2018/03/14 15:20:08 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MALLOC_H
#define MALLOC_H

# include <pthread.h>
# include <sys/mman.h>
# include "../libft/incl/printf.h"

/**
 * 							SLAB DESIGN
 *
 * Each slab will be divided into 'tiny' and 'medium' sections
 * the tiny sections will be 64 bytes, medium will be 1024
 * tiny sections will start at the end of the memory space, and small
 * at the begining.
 * block splitting will be implemented to reclaim memory
 * from the small section and grant it to the tiny if possible
 *
 * All large allocations will only reside in the head slab node.
 *
 **/

/**
 * 							NAMING EXPLAINATION
 * TNYSZ:	Size of user space in a tiny block
 * SMLSZ:	Size of user space in a small block
 * BLKCNT:	Amount of blocks for each size
 * SBLKSZ:	Size of the t_block struct
 * SSLBSZ:	Size of the t_slab struct
 * SLBSZ:	Size of an entire 'slab'
 *
 **/

# define TNYSZ 88
# define SMLSZ 1048
# define BLKCNT 128
# define SBLKSZ sizeof(t_block)
# define SSLBSZ sizeof(t_slab)
# define SLBSZ (SSLBSZ + (((SBLKSZ + TNYSZ) * BLKCNT) + ((SBLKSZ + SMLSZ) * BLKCNT)))


typedef struct      s_slab
{
    struct s_slab   *next;
	struct s_block	*tiny;
	struct s_block	*tiny_que;
	size_t			tiny_avail;
	struct s_block	*small;
	struct s_block	*small_que;
	size_t			small_avail;
	struct s_block	*large;

}                   t_slab;

typedef struct		s_block
{
	struct s_block	*next;
	struct s_block	*prev;
	struct s_slab   *mgr;
	t_blean			avail;
	size_t 			data_size;
}					t_block;

typedef struct		s_mgr
{
	t_slab			*head_slab;
	t_block			*b;
	t_slab			*s;
    size_t			large_cnt;
    size_t			total_frees;
    size_t 			large_frees;
    size_t			freed_bytes;
    size_t			total_allocs;
    size_t			allocated_bytes;
    size_t 			requested_bytes;
}					t_mgr;


t_mgr *g_mgr = NULL;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
void	show_alloc_mem(void);
t_mgr	*get_mgr(t_blean debug);
void	init_mgr(t_mgr *mgr);
void	init_slab(t_slab *slab);
void	init_block(t_block *blk);
t_slab	*create_slab(t_mgr *mgr);
t_block *find_smlblk(t_mgr *mgr);
t_block *find_tnyblk(t_mgr *mgr);
t_block *find_lrgblk(t_mgr *mgr, size_t size);
void	link_blocks(t_slab *mgr, t_block *group, size_t count, size_t size);
t_block	*check_queue(t_slab *slb, size_t blksz);
void	convert_to_tiny(t_slab *slb);
void 	convert_to_small(t_slab *slb);
int     slab_len(t_slab *list);


#endif
