/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dauie <dauie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:39:48 by dauie             #+#    #+#             */
/*   Updated: 2018/03/14 15:15:15 by dauie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "incl/malloc.h"
#include <unistd.h>


int		main(void) {
	size_t ret;
	size_t blocksize = 100;
	ft_printf("blkStructSz: %zu\n", SBLKSZ);
	ft_printf("slbStructSz:\t%zu\n", TNYSZ);
	ft_printf("tiny combin:\t%zu\n", TNYSZ + SBLKSZ);
	ft_printf("small combin:\t%zu\n", SMLSZ + SBLKSZ);
    ft_printf("tiny total:\t%zu\n", (TNYSZ + SBLKSZ) * BLKCNT);
    ft_printf("small total:\t%zu\n", (SMLSZ + SBLKSZ) * BLKCNT);
    ft_printf("total divided:\t%zu\n",  (((SMLSZ + SBLKSZ) * BLKCNT) + (((SMLSZ + SBLKSZ) * BLKCNT)) + SSLBSZ) / 4096);
	while (blocksize < 512) {
		ret = sizeof(t_slab) +
			  (((sizeof(t_block) + TNYSZ) * blocksize) +
			   ((sizeof(t_block) + SMLSZ) * blocksize));
        size_t smallSlab = (sizeof(t_block) + SMLSZ) * blocksize;
        size_t tinySlab = (sizeof(t_block) + TNYSZ) * blocksize;
		printf("%s %zu pages: %f - %zu bytes - small: %zu : %f tiny: %zu : %f\n", "blockcount:", blocksize, (float) ret / getpagesize(),  ret, smallSlab, (float)smallSlab / getpagesize(), tinySlab, (float)tinySlab / getpagesize());
		blocksize++;
	}
////	 Data Structure sizes
	ft_printf("%s %i\n", "page size:", getpagesize());
	     ret = sizeof(t_slab) +
				 (((sizeof(t_block) + TNYSZ) * BLKCNT) +
				  ((sizeof(t_block) + SMLSZ) * BLKCNT));
	ft_printf("%s %zu\n", "tblock size:", sizeof(t_block));
	ft_printf("%s %zu\n", "tslab size:", sizeof(t_slab));
	ft_printf("%s %zu\n", "actual slab size", ret);
}

//char	*randString(void){
//	return ((char *)malloc(rand() % 1254));
//}
//
//////			Randomly Generated String Test
//int		main(void) {
//	srand(1234);
//
//	char **str;
//	int size = 1000;
//	str = malloc(sizeof(char *) * (size + 1));
//	char *reStr = NULL;
//	for(int i = 0; i < size; i ++) {
//		for (int i = 0; i < size; i++) {
//			str[i] = randString();
//		}
//		for (int i = 0; i < size; i++) {
//			free(str[i]);
//		}
//		reStr = randString();
//		reStr = realloc(reStr, ft_strlen(reStr) + 42);
//		ft_strcpy(reStr + ft_strlen(reStr), "helllllllllla");
//		reStr = realloc(reStr, ft_strlen(reStr) + 84);
//		free(reStr);
//	}
//	free(str);
//	show_alloc_mem();
//}


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
