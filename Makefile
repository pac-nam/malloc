NAME = libft_malloc_$(HOSTTYPE).so
SHORTNAME = libft_malloc.so

ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

###############################
####### GLOBAL VARIABLE #######
###############################
SRCSDIR 	= 	srcs
OBJSDIR 	= 	objs
INCLUDES 	= 	includes
DEBUG		=	-g3
CFLAGS 		=  	-Wall -Werror -Wextra -Wpadded
CC 			= 	gcc $(CFLAGS) $(DEBUG)
HEADER		=	liballoc.h
HEADERS		=	$(addprefix $(INCLUDES)/, $(HEADER))
LIBDIR		=	libft
LIB			=	libft.a
###############################
######## CREATE FOLDER ########
####### C FILE BY FOLDER ######
###############################

SRC     =		malloc.c free.c realloc.c calloc.c show_alloc_mem.c reallocf.c malloc_good_size.c
###############################
######### ADD PREFIX ##########
###### ALL SRC/OBJ FILE #######
###############################

OBJ 		= 	$(SRC:%.c=%.o)

SRCS 		= 	$(addprefix $(SRCSDIR)/, $(SRC))
OBJS 		= 	$(addprefix $(OBJSDIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(LIBDIR)/$(LIB) $(OBJSDIR) $(OBJS)
	@$(CC) -shared -o $(NAME) $(OBJS) $(LIBDIR)/$(LIB)
	@rm -rf libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo "\033[32m[ ✔ ] $@ compiled\033[0m"

compile:
	@gcc tests/test0.c  -Iincludes/ -o tests/test0
	@gcc tests/test1.c -Iincludes/ -o tests/test1
	@gcc tests/test2.c -Iincludes/ -o tests/test2
	@gcc tests/test3.c -Iincludes/ -o tests/test3
	@gcc tests/test3++.c -Iincludes/ -o tests/test3++
	@gcc tests/test4.c -Iincludes/ -o tests/test4
	@gcc tests/test5.c -Iincludes/ -L. -lft_malloc -o tests/test5
	@echo "Compiling tests"

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADERS)
	@$(CC) -c -o $@ $< -I$(INCLUDES)

$(LIBDIR)/$(LIB):
	@make -C $(LIBDIR)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)/$(DIRCORE)

clean:
	@make clean -C $(LIBDIR)
	@/bin/rm -rf $(OBJSDIR);
	@echo "\033[33m[ ✔ ] $(NAME) objects deleted\033[0m"

fclean: clean
	@make fclean -C $(LIBDIR)
	@/bin/rm -f $(NAME) $(SHORTNAME)
	@rm -rf $(NAME).dSYM
	@echo "\033[33m[ ✔ ] $(NAME) deleted\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re, $(OBJSDIR)/$(DIRCORE), $(compile)

.SUFFIXES: .c .o
