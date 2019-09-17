/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/09/12 16:20:14 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liballoc.h"

void		*ft_find_cluster(t_block *block, int size)
{
	//write(1, "find cluster\n", 13);
	t_block		*tmp_block;
	t_cluster	*cluster;

	size = malloc_good_size(size);
	//printf("BALISE1 %d\n", size);
	tmp_block = block;
	while (tmp_block)
	{
		cluster = (void*)tmp_block + BLOCKSIZE;
		while ((void*)cluster < (void*)tmp_block + tmp_block->size)
		{
			//sleep(1);
			if (cluster->freesize >= size + (int)CLUSTERSIZE
			|| cluster->freesize == size)
			{
				//ft_bzero((void*)cluster + CLUSTERSIZE, size - CLUSTERSIZE);
				if (cluster->freesize >= size + (int)CLUSTERSIZE)
					((t_cluster*)((void*)cluster + size))->freesize
					= cluster->freesize - size;
				cluster->freesize = -size;
				return ((void*)cluster + CLUSTERSIZE);
			}
			cluster = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
			//sleep(1);
		}
		tmp_block = tmp_block->next;
	}
	//ft_putendl("space not found");
	//write(1, "no space\n", 9);
	return (NULL);
}

void		*ft_new_page(t_block **block, size_t size)
{
	size_t		alloc_length;
	t_block		*new_block;
	t_cluster	*new_cluster;

	alloc_length = PAGESIZE;
	while ((size <= TINY && alloc_length
	< (TINY + CLUSTERSIZE) * 100 + BLOCKSIZE)
	|| (TINY < size && size <= SMALL
	&& alloc_length < (SMALL + CLUSTERSIZE) * 100 + BLOCKSIZE))
		alloc_length += PAGESIZE;
	if (SMALL < size)
		alloc_length = size + CLUSTERSIZE + BLOCKSIZE;
	if ((new_block = mmap(0, alloc_length, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->size = alloc_length;
	new_block->next = *block;
	*block = new_block;
	new_cluster = (void*)new_block + BLOCKSIZE;
	if (size <= SMALL)
		new_cluster->freesize = new_block->size - BLOCKSIZE;
	else
		new_cluster->freesize = -1;
	//write(1, "new page\n", 9);
	return ((void*)new_cluster + CLUSTERSIZE);
}

void		*malloc(size_t size)
{
	ft_putnbr((int)size);
	ft_blue(" malloc start\n");
	void	*result;

	result = NULL;
	if (size != 0)
	{
		if (size <= TINY)
		{
			if (!(result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE)))
				if (ft_new_page(&g_alloc.tiny, TINY))
					result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE);
		}
		else if (size <= SMALL)
		{
			//ft_putendl("alloc small");
			if (!(result = ft_find_cluster(g_alloc.small, size + CLUSTERSIZE)))
				if (ft_new_page(&g_alloc.small, SMALL))
					result = ft_find_cluster(g_alloc.small, size + CLUSTERSIZE);
		}
		else
			result = ft_new_page(&g_alloc.large, size);
	}
	ft_putaddr(result);
	ft_putstr(" malloc end allocated: ");
	ft_putnbr(-((t_cluster*)((void*)result - CLUSTERSIZE))->freesize);
	ft_putstr(" - 16 = ");
	ft_putnbr_n(-((t_cluster*)((void*)result - CLUSTERSIZE))->freesize - 16);
	//show_alloc_mem();
	return (result);
}
