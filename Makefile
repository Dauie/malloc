ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$HOSTTYPE.so

CC = gcc


CCFLAGS = -Wall -Werror -Wextra -g -O0 -shared

SRC = src/allocator.c src/malloc.c src/free.c src/realloc.c src/calloc.c src/struct_init.c

OBJ = *.o

RM = -rm -fr

$(NAME):
		$(MAKE) -C ./libft/ re
		$(CC) $(CCFLAGS) $(SRC) ./libft/libftprintf.a -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)
