/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dauie <dauie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:39:48 by dauie             #+#    #+#             */
/*   Updated: 2018/01/08 09:46:14 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "incl/malloc.h"
//#include <unistd.h>

//int		main(void) {

//	size_t blocksize = 100;
//	while (blocksize < 256) {
//		ret = sizeof(t_slab) +
//			  (((sizeof(t_block) + TINYSIZE) * blocksize) +
//			   ((sizeof(t_block) + SMALLSIZE) * blocksize));
//		printf("%s %zu %f\n", "blockcount:", blocksize, (float)ret / getpagesize());
//		blocksize++;
//	}
//}

int		main(void) {
	ft_printf("%s %i\n", "page size:", getpagesize());
	ft_printf("%s %i\n", "defined slab size", SLBSZ);
	size_t ret = sizeof(t_slab) +
				 (((sizeof(t_block) + TNYSZ) * BLKCNT) +
				  ((sizeof(t_block) + SMLSZ) * BLKCNT));
	ft_printf("%s %zu\n", "tblock size:", sizeof(t_block));
	ft_printf("%s %zu\n", "tslab size:", sizeof(t_slab));
	ft_printf("%s %zu\n", "actual slab size", ret);
	ft_printf("%s %zu\n", "data overhead:", sizeof(t_slab) + (sizeof(t_block) * BLKCNT));
//	ft_printf("%s %f\n", "slabsize / pagesize:", (float)ret / getpagesize());
	char *test;
	char str[] = "Fella Fella Fella";
	for(int i = 0; i < 200; i++) {
		test = ft_strdup(str);
	}
    show_alloc_mem();
}