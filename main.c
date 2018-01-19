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
//	printf("%s %i\n", "page size:", getpagesize());
//	printf("%s %i\n", "defined slab size", SLABSIZE);
//	size_t ret = sizeof(t_slab) +
//			(((sizeof(t_block) + TINYSIZE) * BLOCKCOUNT) +
//			((sizeof(t_block) + SMALLSIZE) * BLOCKCOUNT));
//	printf("%s %zu\n", "tblock size:", sizeof(t_block));
//	printf("%s %zu\n", "tslab size:", sizeof(t_slab));
//	printf("%s %zu\n", "actual slab size", ret);
//	printf("%s %zu\n", "data overhead:", sizeof(t_slab) + (sizeof(t_block) * BLOCKCOUNT));
//	printf("%s %f\n", "slabsize / pagesize:", (float)ret / getpagesize());
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
	char *test;
	char str[] = "hella hella hella";
	while (1) {
		test = ft_strdup(str);
		ft_printf("%s\n", test);
	}
}