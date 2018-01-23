/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dauie <dauie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:39:48 by dauie             #+#    #+#             */
/*   Updated: 2018/01/21 12:58:33 by dauie            ###   ########.fr       */
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
//////	 Data Structure sizes
//	ft_printf("%s %i\n", "page size:", getpagesize());
//	ft_printf("%s %i\n", "defined slab size", SLBSZ);
//	     ret = sizeof(t_slab) +
//				 (((sizeof(t_block) + TNYSZ) * BLKCNT) +
//				  ((sizeof(t_block) + SMLSZ) * BLKCNT));
//	ft_printf("%s %zu\n", "tblock size:", sizeof(t_block));
//	ft_printf("%s %zu\n", "tslab size:", sizeof(t_slab));
//	ft_printf("%s %zu\n", "actual slab size", ret);
//}
//
char	*randString(void){
	return ((char *)malloc(rand() % 1254));
}

//			Randomly Generated String Test
int		main(void) {
	srand(1234);
//	show_alloc_mem();



	char **str;
	int size = 20000;
	str = malloc(sizeof(char *) * (size + 1));
		for(int i = 0; i < 42; i ++) {
			for (int i = 0; i < size; i++) {
				str[i] = randString();
			}
			for (int i = 0; i < size; i++) {
				free(str[i]);
			}
			for (int i = 0; i < size; i++) {
				str[i] = randString();
			}
			for (int i = 0; i < size; i++) {
				free(str[i]);
			}
			for (int i = 0; i < size; i++) {
				str[i] = randString();
			}
			for (int i = 0; i < size; i++) {
				free(str[i]);
			}
			for (int i = 0; i < size; i++) {
				str[i] = randString();
			}
			for (int i = 0; i < size; i++) {
				free(str[i]);
			}
		}
	free(str);
	show_alloc_mem();
}


//int 		main(void){
//	int fd = 0;
//	char *ret;
//	char **tbl;
//	char **tmp;
//
//	tbl = NULL;
//	fd = open("test.txt", O_RDONLY);
//	while (gnl(fd, &ret)){
//		tmp = tbl;
//		tbl = ft_tbladdl(tbl,ret);
//		ft_tbldel(tmp, (int)ft_tbllen(tmp));
//		free(ret);
//	}
//	close(fd);
//	fd = open("test.txt", O_RDONLY);
//	while (gnl(fd, &ret)){
//		tmp = tbl;
//		tbl = ft_tbladdl(tbl,ret);
//		ft_tbldel(tmp, (int)ft_tbllen(tmp));
//		free(ret);
//	}
//	close(fd);
//	fd = open("test.txt", O_RDONLY);
//	while (gnl(fd, &ret)){
//		tmp = tbl;
//		tbl = ft_tbladdl(tbl,ret);
//		ft_tbldel(tmp, (int)ft_tbllen(tmp));
//		free(ret);
//	}
//	while (gnl(fd, &ret)){
//		tmp = tbl;
//		tbl = ft_tbladdl(tbl,ret);
//		ft_tbldel(tmp, (int)ft_tbllen(tmp));
//		free(ret);
//	}
//	close(fd);
//	fd = open("test.txt", O_RDONLY);
//	while (gnl(fd, &ret)){
//		tmp = tbl;
//		tbl = ft_tbladdl(tbl,ret);
//		ft_tbldel(tmp, (int)ft_tbllen(tmp));
//		free(ret);
//	}
//	for (int i = 0; i < (int)ft_tbllen(tbl); i++){
//		ft_printf("%s\n", tbl[i]);
//	}
//	ft_tbldel(tbl, (int)ft_tbllen(tbl));
//	show_alloc_mem();
//}
