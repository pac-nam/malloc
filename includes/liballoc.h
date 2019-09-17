/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lialloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBALLOC_H
# define LIBALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef	struct			s_cluster
{
	int				freesize;
}						t_cluster;

typedef struct 			s_block
{
	size_t				size;
	struct s_block		*next;
}						t_block;

typedef struct			s_context
{
	t_block				*tiny;
	t_block				*small;
	t_block				*large;
}						t_context;

t_context				g_alloc;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
t_block *ft_get_malloc_page(void *ptr);
int     ft_check_ptr(t_block *page, void *to_find);
size_t	malloc_good_size(size_t x);

# define TINY	2048
# define SMALL	1024*128
# define ALIGN	16
# define PAGESIZE getpagesize()
# define BLOCKSIZE malloc_good_size(sizeof(t_block))
# define CLUSTERSIZE malloc_good_size(sizeof(t_cluster))

#endif

#include <stdio.h>