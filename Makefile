# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 10:34:52 by tbleuse           #+#    #+#              #
#    Updated: 2019/09/12 16:14:23 by tbleuse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE)

LINK = libft_malloc.so

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

LIBFT = libft

LIB = $(LIBFT)/$(LIBFT).a

SRC_FOLDER = srcs

INCLUDE_FOLDER = includes

OBJ_FOLDER = objs

TESTFILE = main_test.c

SRC	=	malloc.c			\
		show_alloc_mem.c	\
		free.c				\
		realloc.c			\
		malloc_good_size.c	\

OBJ = $(addprefix $(OBJ_FOLDER)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_FOLDER) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -I $(INCLUDE_FOLDER) $(LIB) -shared -o $(NAME).so
	@echo "\033[32m[ ✔ ] $@ compiled\033[0m"
	@/bin/rm -f $(LINK)
	@ln -fs $(NAME).so $(LINK)
	@echo "$@ is linked to the system"

$(OBJ_FOLDER):
	@mkdir -p $@
	@echo "creating $(NAME) object..."

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@$(CC) -I $(INCLUDE_FOLDER) $(FLAGS) -c $< -o $@

lib : all clean

clean : $(LIBFT)clean
	@/bin/rm -rf $(OBJ_FOLDER)
	@/bin/rm $(LINK)
	@echo "\033[33m[ ✔ ] $(NAME) objects deleted\033[0m"

fclean : $(LIBFT)fclean
	@/bin/rm -rf $(OBJ_FOLDER)
	@/bin/rm -f $(LINK)
	@echo "\033[33m[ ✔ ] $(NAME) objects deleted\033[0m"
	@/bin/rm -f $(NAME).so
	@echo "\033[33m[ ✔ ] $(NAME) deleted\033[0m"

re : fclean all

$(LIBFT):
	@make -C $(LIBFT)

$(LIBFT)clean:
	@make clean -C $(LIBFT)

$(LIBFT)fclean:
	@make fclean -C $(LIBFT)

.PHONY: $(LIBFT) $(OBJ_FOLDER)
