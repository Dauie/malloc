/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dauie <dauie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:39:48 by dauie             #+#    #+#             */
/*   Updated: 2018/01/19 22:26:54 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "incl/malloc.h"
//#include <unistd.h>

//int		main(void) {
//	size_t ret;
//	size_t blocksize = 100;
//	ft_printf("struct:\t%zu\n", SBLKSZ);
//	ft_printf("tinyzs:\t%zu\n", TNYSZ);
//	ft_printf("combin:\t%zu\n", TNYSZ + SBLKSZ);
//	while (blocksize < 512) {
//		ret = sizeof(t_slab) +
//			  (((sizeof(t_block) + TNYSZ) * blocksize) +
//			   ((sizeof(t_block) + SMLSZ) * blocksize));
//		printf("%s %zu %f\n", "blockcount:", blocksize, (float) ret / getpagesize());
//		blocksize++;
//	}
//}

char	*randString(void){

	int len = rand() % 50;
	char *ret = ft_strnew(len);
	for (int i = 0; i < len; i++) {
		ret[i] = (char)(rand() % (char)122);
	}
	return (ret);
}

int		main(void) {
	srand(time(NULL));
	show_alloc_mem();

////	 Data Structure sizes
	ft_printf("%s %i\n", "page size:", getpagesize());
	ft_printf("%s %i\n", "defined slab size", SLBSZ);
	size_t ret = sizeof(t_slab) +
				 (((sizeof(t_block) + TNYSZ) * BLKCNT) +
				  ((sizeof(t_block) + SMLSZ) * BLKCNT));
	ft_printf("%s %zu\n", "tblock size:", sizeof(t_block));
	ft_printf("%s %zu\n", "tslab size:", sizeof(t_slab));
	ft_printf("%s %zu\n", "actual slab size", ret);

	char **str;
	int size = 20000;
	str = ft_memalloc(sizeof(char *) * (size + 1));
	for(int i = 0; i < size; i++) {
		str[i] = randString();
	}
	for(int i = 0; i < size; i++) {
		ft_printf("%s\n", str[i]);
	}
	for(int i = 0; i < size; i++) {
		free(str[i]);
	}
	free(str);
	show_alloc_mem();
}