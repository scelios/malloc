ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# **************************************************************************** #
# FILES             														   #
# **************************************************************************** #

PATH_INC = .
PATH_LIB = .
PATH_OBJ = obj
PATH_SRC = .

SOURCES += shared.c \
                          findBlock.c \
                          divide.c \
                          createHeap.c \
                          helper.c \
                          malloc.c \
						  log.c \
						  free.c \
						  realloc.c \
						  calloc.c \
							libc/ft_itoa_base.c \
							libc/ft_bzero.c \
							libc/ft_putstr.c \
							libc/ft_putchar_fd.c\
							libc/ft_memcpy.c \
							libc/ft_memmove.c\
							libc/ft_memset.c\
							libc/ft_putstr_fd.c \
							printf/ft_printf.c \
							printf/ft_putchar_printf.c \
							printf/ft_putnbr_base_printf.c \
							printf/ft_putnbr_printf.c \
							printf/ft_putstr_printf.c \


OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

# **************************************************************************** #
# VARIABLES         														   #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc

FLAGS_CC = -Wall -Wextra -Werror -fPIC
FLAGS_LIB = -shared

# **************************************************************************** #
# COMMANDS  		    													   #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS_LIB) -o $@ $(OBJECTS)
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)
	@echo "Make done"

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(FLAGS_CC) $^ -O0 -g -I $(PATH_INC)

clean:
	@rm -rf $(PATH_OBJ)
	@echo "Clean done"

fclean: clean
	@rm -f $(NAME) $(LIB_NAME)
	@echo "Fclean done"

re: fclean $(NAME)