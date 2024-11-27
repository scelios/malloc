#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := a.out
CC        := gcc
FLAGS    := 
################################################################################
#                                 PROGRAM'S SRCS                               #
###############################################################################

SRCS        :=      shared.c \
                          findBlock.c \
                          divide.c \
                          createHeap.c \
                          helper.c \
                          malloc.c \
						  log.c \
						  free.c \
						  realloc.c \
						  calloc.c \
						  reallocf.c \
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
							src/main.c \
							src/print.c \
							src/test_limit.c \
							src/test_malloc.c \
							src/test_mixed.c \
							src/test_realloc.c

OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


