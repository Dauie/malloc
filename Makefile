ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -shared -ldl

SRC = src/allocator.c src/malloc.c src/free.c src/realloc.c src/calloc.c src/struct_init.c src/find_block.c \
        src/show_alloc_mem.c src/optimize.c src/utility.c

OBJ = *.o

RM = -rm -fr

$(NAME):
		$(MAKE) -C ./libft/ re
		$(CC) -fPIC -c $(SRC)
		$(CC) $(CFLAGS) $(LDFLAGS) ./libft/libftprintf.a $(OBJ) -o $(NAME)
		ln -s $(NAME) libft_malloc.so

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
		$(RM) libft_malloc.so

re: fclean $(NAME)
