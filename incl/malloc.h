/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:25:30 by rlutt             #+#    #+#             */
/*   Updated: 2018/07/08 13:58:01 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>
# include <sys/mman.h>
# include "../libft/incl/printf.h"

# define TNYSZ 32
# define SMLSZ 480
# define BLKCNT 128
# define SBLKSZ sizeof(t_block)
# define SSLBSZ sizeof(t_slab)
# define SLSLBSZ sizeof(t_lslab)
# define TNYSEC ((SBLKSZ + TNYSZ) * BLKCNT)
# define SMLSEC ((SBLKSZ + SMLSZ) * BLKCNT)
# define SLBSZ (SSLBSZ + (SMLSEC + TNYSEC))

extern pthread_mutex_t g_mux;

typedef union		s_mgru
{
	struct s_slab	*slb;
	struct s_lslab	*lslb;
}					t_mgru;


typedef struct		s_slab
{
	size_t			tiny_avail;
	size_t			small_avail;
	size_t			size;
    struct s_block	*tiny_que;
    struct s_block	*small_que;
	struct s_block	*tiny;
	struct s_block	*small;
	struct s_slab	*next;
}					t_slab;

typedef	struct		s_lslab
{
	unsigned long	totbytes;
	unsigned long 	availbytes;
	size_t 			blkfree;
	size_t 			blkcnt;
	struct s_block	*large;
	struct s_block  *large_end;
	struct s_lslab	*next;
}					t_lslab;

typedef struct		s_block
{
	struct s_block	*next;
	t_mgru			mgr;
	size_t			data_size;
	size_t			avail;
}					t_block;


typedef struct		s_mgr
{
	t_slab			*head_slab;
    struct s_lslab	*large;
	size_t			large_cnt;
	size_t			total_frees;
	size_t			large_frees;
	size_t			freed_bytes;
	size_t			total_allocs;
	size_t			allocated_bytes;
	size_t			requested_bytes;
}					t_mgr;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				clean_allocations(t_mgr *mgr);
void				show_alloc_mem(void);
void				*alloc_large(t_mgr *mgr, size_t size);
void				*alloc_block(t_mgr *mgr, size_t size);
t_mgr				*get_mgr(t_blean debug);
void				init_mgr(t_mgr *mgr);
void				init_slab(t_slab *slab);
void				init_block(t_block *blk);
void				init_lslab(t_lslab *slab);
t_slab				*create_slab(t_mgr *mgr);
t_block				*find_slb_blk(t_mgr *mgr, size_t size);
t_lslab				*make_lrgslb(t_mgr *mgr, size_t size);
int					slab_len(t_slab *list);
t_blean				is_allocated(t_mgr *mgr, void **ptr);

#endif

