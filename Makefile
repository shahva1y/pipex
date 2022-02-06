NAME = pipex
NAME_BONUS = pipex

SRCS = 	pipex.c utils.c
SRCS_BONUS = pipex_bonus.c utils_bonus.c ft_here_doc_bonus.c

LIB = libft.a
LIB_SRC = ./libft

OBJS = $(SRCS:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)
HEADER = pipex.h
HEADER_BONUS = pipex_bonus.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(HEADER)

.PHONY	: all clean fclean re bonus

all		: $(LIB) $(NAME)

$(NAME)	: $(OBJS) $(LIB_SRC)/$(LIB)
ifeq ($(SRCS), pipex_bonus.c utils_bonus.c ft_here_doc_bonus.c)
	$(CC) $(OBJS_BONUS) $(LIB_SRC)/$(LIB) -o $(NAME)
else
	rm -f $(OBJS_BONUS)
	$(CC) $(OBJS) $(LIB_SRC)/$(LIB) -o $(NAME)
endif

$(LIB)	:
	make all -C $(LIB_SRC)

%.o		: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	$(MAKE) clean -C $(LIB_SRC)
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean	: clean
	$(MAKE) fclean -C $(LIB_SRC)
	rm -f $(NAME)

bonus	:
	rm -f $(OBJS)
	make SRCS='$(SRCS_BONUS)' HEADER='$(HEADER_BONUS)' all

re		: fclean all
