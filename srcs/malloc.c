/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liballoc.h"

size_t		ft_align(size_t x)
{
	return ((x + 15) / 16) * 16;
}

void		*ft_find_cluster(t_block *block, short size)
{
	t_block		*tmp_block;
	t_cluster	*cluster;

	tmp_block = block;
	while (tmp_block)
	{
		cluster = (void*)tmp_block + BLOCKSIZE;
		while ((void*)cluster < (void*)tmp_block + tmp_block->size)
		{
			if (cluster->freesize >= size + (int)CLUSTERSIZE)
			{
				ft_bzero(cluster + CLUSTERSIZE, size - CLUSTERSIZE);
				(cluster + size)->freesize = cluster->freesize - size;
				cluster->freesize = -size;
				//printf("\nold cluster  %p\n", cluster);
				//printf("new cluster %p\n", cluster + size);
				//printf("metadata %p\n", cluster);
				//printf("return   %p\n\n", cluster + CLUSTERSIZE);
				return cluster + CLUSTERSIZE;
			}
			//printf("&cluster + %ld  %p\n", ft_align(ft_abs(cluster->freesize)), cluster + ft_align(ft_abs(cluster->freesize)));
			cluster += ft_abs(cluster->freesize);
			//printf("&cluster2 %p\n", cluster);
		}
		tmp_block = tmp_block->next;
	}
	//ft_putendl("space not found");
	return (NULL);
}

void		*ft_new_page(t_block *block, size_t size)
{
	size_t		alloc_length;
	t_block		*new_block;
	t_cluster	*new_cluster;

	alloc_length = PAGESIZE;
	while ((size <= TINY && alloc_length < (TINY * 4 + CLUSTERSIZE) * 100 + BLOCKSIZE)
	|| (TINY < size && size <= SMALL && alloc_length < (SMALL * 4 + CLUSTERSIZE) * 100 + BLOCKSIZE)
	|| (SMALL < size && alloc_length < size + CLUSTERSIZE + BLOCKSIZE))
		alloc_length += PAGESIZE;
	if ((new_block = mmap(0, alloc_length, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->size = alloc_length;
	new_block->next = block;
	new_cluster = (void*)new_block + BLOCKSIZE;
	new_cluster->freesize = (new_block->size - BLOCKSIZE) / 4;
	if (size <= TINY)
		g_alloc.tiny = new_block;
	else if (size <= SMALL)
		g_alloc.small = new_block;
	else
	{
		g_alloc.large = new_block;
		new_cluster->freesize = -1;
	}
	return (new_cluster + CLUSTERSIZE);
}

void		*ft_malloc(size_t size)
{
	void	*result;

	result = NULL;
	if (size == 0)
		return (NULL);
	size = ft_align(size) / 4;
	if (size <= TINY)
	{
		if ((result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE)) == NULL)
			if (ft_new_page(g_alloc.tiny, TINY))
				result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE);
	}
	else if (size <= SMALL)
	{
		if ((result = ft_find_cluster(g_alloc.small, size + CLUSTERSIZE)) == NULL)
			if (ft_new_page(g_alloc.small, SMALL))
				result = ft_find_cluster(g_alloc.small, size + CLUSTERSIZE);
	}
	else
		result = ft_new_page(g_alloc.large, size);
	return (result);
}