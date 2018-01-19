/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dauie <dauie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:39:48 by dauie             #+#    #+#             */
/*   Updated: 2018/01/19 15:04:12 by dauie            ###   ########.fr       */
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
//	ft_printf("%s %i\n", "page size:", getpagesize());
//	ft_printf("%s %i\n", "defined slab size", SLBSZ);
//	size_t ret = sizeof(t_slab) +
//				 (((sizeof(t_block) + TNYSZ) * BLKCNT) +
//				  ((sizeof(t_block) + SMLSZ) * BLKCNT));
//	ft_printf("%s %zu\n", "tblock size:", sizeof(t_block));
//	ft_printf("%s %zu\n", "tslab size:", sizeof(t_slab));
//	ft_printf("%s %zu\n", "actual slab size", ret);
//	ft_printf("%s %zu\n", "data overhead:", sizeof(t_slab) + (sizeof(t_block) * BLKCNT));


	int fd = open("CMakeLists.txt", O_RDONLY);
	char *str;
//	char *str2;

	//GNL TEST
//	while(gnl(fd, &str)) {
//		ft_printf("%s\n", str);
//		free(str);
//	}
//	close(fd);
//	fd = open("CMakeLists.txt", O_RDONLY);
//	while(gnl(fd, &str)) {
//		ft_printf("%s\n", str);
//		free(str);
//	}
//	close(fd);
//	fd = open("CMakeLists.txt", O_RDONLY);
	void *test;
	test = malloc(100);
	free(test);
	show_alloc_mem();

	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}
	close(fd);
	fd = open("CMakeLists.txt", O_RDONLY);
	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}
	close(fd);
	fd = open("CMakeLists.txt", O_RDONLY);
	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}
	close(fd);
	fd = open("CMakeLists.txt", O_RDONLY);
	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}
	close(fd);
	fd = open("CMakeLists.txt", O_RDONLY);
	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}
	close(fd);
	fd = open("CMakeLists.txt", O_RDONLY);
	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}
	close(fd);
	fd = open("CMakeLists.txt", O_RDONLY);
	while(gnl(fd, &str)) {
		ft_printf("%s\n", str);
		free(str);
	}

	//MALLOC LOTS TEST
//	for (int i = 0; i < 1000; i++){
//		str2 = ft_strdup("hahah");
//		str = ft_strdup("blahasd asldkfjals dfjlasdk fasldkfj asdlfkj asldfasdlfjas dflksadfj alsdfjasldkf ajsdfl;k jasdflkajsd flaksdjf alsdfkjas dlfkjasdflkajsdfl ksadjflkasdfjasl;dkfj sadl;fjasdfl;asdjf als;dfjalsdk fj as dlfkj sad lf;kj sdflkjs adfl kasjdflksadjflsadkjf alsdkfjasdlf");
//	}

    show_alloc_mem();
}