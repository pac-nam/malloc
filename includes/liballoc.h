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

void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	ft_show_alloc_mem(void);
size_t	ft_align(size_t x);

/*typedef struct			s_cluster
{
	void				*start;
	void				*end;
	struct s_cluster	*next;
}						t_cluster;

typedef struct			s_zone
{
	void				*start;
	size_t				length;
	size_t				used;
	t_cluster			*vacant;
	struct s_zone		*next;
}						t_zone;

typedef struct			s_context
{
	t_zone				*tiny;
	t_zone				*small;
	t_zone				*large;
}						t_context;
*/

/*typedef struct 			s_cluster
{
	size_t				size;	// negative size if not used and remove used variable
	int					used;	// bool
}						t_cluster;
*/

typedef	struct			s_cluster
{
	short				freesize;
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

//https://www.cocoawithlove.com/2010/05/look-at-how-malloc-works-on-mac.html
# define TINY	64
# define SMALL	256
# define ALIGN	16
# define PAGESIZE getpagesize()
# define BLOCKSIZE ft_align(sizeof(t_block))
# define CLUSTERSIZE ft_align(sizeof(t_cluster))

#endif

#include <stdio.h>