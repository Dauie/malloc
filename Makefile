ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

OS = $(shell uname)

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

COMMA = ,

SRCDIR = src

OBJDIR = obj

CFLAGS  = -Wall -Werror -Wextra -g

OBJFLAGS = -c -fPIC

EXPORT_SYM = malloc free realloc show_alloc_mem

LDFLAGS = -shared -ldl

ifeq ($(OS),Darwin)
LDFLAGS += $(addprefix -Wl$(COMMA)-exported_symbol$(COMMA)_,$(EXPORT_SYM))
else
ifeq ($(OS),Linux)
LDFLAGS += -fvisibility=hidden -Wl,--version-script=libmalloc.version
endif
endif

INCL = -I incl

LIBFT_INCL = -I./libft/incl

SRC = allocator.c malloc.c free.c realloc.c struct_init.c find_block.c
SRC += show_alloc_mem.c utility.c

OBJS = $(SRC:.c=.o)

SRCFILES = $(addprefix $(SRCDIR)/, $(SRC))

OBJFILES = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJFILES += libft/libftprintf.a

RM = rm -fr

$(NAME): create_obj_dir
		$(MAKE) -C ./libft/ re
		$(CC) $(OBJFLAGS) $(CFLAGS) $(LIBFT_INCL) $(SRCFILES)
		mv $(OBJS) $(OBJDIR)
		$(CC) $(CFLAGS) $(LDFLAGS) $(INCL) $(OBJFILES) -o $(NAME)
		ln -s $(NAME) libft_malloc.so

create_obj_dir:
		@mkdir -p $(OBJDIR)

clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)
		$(RM) libft_malloc.so

re: fclean $(NAME)
