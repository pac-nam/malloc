# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 10:34:52 by tbleuse           #+#    #+#              #
#    Updated: 2018/10/23 13:48:46 by tbleuse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liballoc

LIBFT = libft

FLAGS = -Wall -Wextra -Werror

SRC_NAME	=	malloc.c			\
				show_alloc_mem.c	\
				free.c				\
				realloc.c			\

SRC = $(addprefix src/, $(SRC_NAME))

OBJ = $(SRC:.c=.o)

TESTFILE = main_test.c

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(NAME).a

$(LIBFT):
	make -C $(LIBFT)

$(LIBFT)clean:
	make clean -C $(LIBFT)

$(LIBFT)fclean:
	make fclean -C $(LIBFT)

$(LIBFT)re:
	make re -C $(LIBFT)

%.a: $(OBJ)
	@ar rc $(NAME).a $(OBJ)
	@ranlib $(NAME).a
	@printf '\n\033[32m[ ✔ ] %s %s\n\033[0m' $(NAME) "compiled"

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@
	@printf '\x1b[42m%c\x1b[0m' "|"

clean: $(LIBFT)clean
	@/bin/rm -f $(OBJ)
	@printf '\033[33m[ ✔ ] %s %s\n\033[0m' $(NAME) "objects deleted"

fclean: $(LIBFT)fclean
	@/bin/rm -f $(OBJ)
	@printf '\033[33m[ ✔ ] %s %s\n\033[0m' $(NAME) "objects deleted"
	@/bin/rm -f $(NAME).a
	@printf '\033[33m[ ✔ ] %s %s\n\033[0m' $(NAME) "deleted"

lib: all clean

re: fclean all

test: all
	@gcc -Wall -Wextra -Werror -o test_malloc.exe $(TESTFILE) $(NAME).a libft/$(LIBFT).a
	@./test_malloc.exe
	@rm test_malloc.exe

.PHONY: all clean fclean re test $(LIBFT)
