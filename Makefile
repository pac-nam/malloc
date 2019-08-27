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

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

SRC_FOLDER = srcs

INCLUDE_FOLDER = includes

OBJ_FOLDER = objs

TESTFILE = main_test.c

SRC	=	malloc.c			\
		show_alloc_mem.c	\
		free.c				\
		realloc.c			\

OBJ = $(addprefix $(OBJ_FOLDER)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_FOLDER) $(OBJ)
	@ar rc $(NAME).a $(OBJ)
	@ranlib $(NAME).a
	@echo "\033[32m[ ✔ ] $@ compiled\033[0m"

$(OBJ_FOLDER):
	@mkdir -p $@
	@echo "creating $(NAME) object..."

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@$(CC) -I $(INCLUDE_FOLDER) $(FLAGS) -c $< -o $@

test: all
	@gcc -Wall -Wextra -Werror -o test_malloc.exe $(TESTFILE) $(NAME).a $(LIBFT)/$(LIBFT).a
	@./test_malloc.exe
	@rm test_malloc.exe

lib : all clean

clean : $(LIBFT)clean
	@/bin/rm -rf $(OBJ_FOLDER)
	@echo "\033[33m[ ✔ ] $(NAME) objects deleted\033[0m"

fclean : $(LIBFT)fclean
	@/bin/rm -rf $(OBJ_FOLDER)
	@echo "\033[33m[ ✔ ] $(NAME) objects deleted\033[0m"
	@/bin/rm -f $(NAME).a
	@echo "\033[33m[ ✔ ] $(NAME) deleted\033[0m"

re : fclean all

$(LIBFT):
	@make -C $(LIBFT)

$(LIBFT)clean:
	@make clean -C $(LIBFT)

$(LIBFT)fclean:
	@make fclean -C $(LIBFT)

.PHONY: $(LIBFT) $(OBJ_FOLDER)