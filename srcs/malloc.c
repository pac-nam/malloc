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

void		*ft_find_cluster(t_block *page, int size)
{
	//write(1, "find cluster\n", 13);
	t_cluster	*cluster;
	//t_cluster	*c2;

	//printf("BALISE1 %d\n", size);
	size += CLUSTERSIZE;
	while (page)
	{
		//ft_putchar('d');
		cluster = (void*)page + BLOCKSIZE;
		while ((void*)cluster < (void*)page + page->size)
		{
			//ft_putchar('e');
			//ft_putaddr(cluster);
			//ft_putstr(" address size ");
			//ft_putnbr_n(cluster->freesize);
			//sleep(1);
			if (cluster->freesize >= size)
			{
				//ft_putchar('f');
				//ft_bzero((void*)cluster + CLUSTERSIZE, size - CLUSTERSIZE);
				if (cluster->freesize >= size + (int)CLUSTERSIZE)
					((t_cluster*)((void*)cluster + size))->freesize
					= cluster->freesize - size;
				//ft_putchar('m');
				cluster->freesize = -size;
				return ((void*)cluster + CLUSTERSIZE);
			}
			//c2 = cluster;
			cluster = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
			//if (cluster == c2)
			//{
			//	show_alloc_mem();
			//	ft_putaddr(c2);
			//	exit(1);
			//}
			//sleep(1);
		}
		//ft_putchar('g');
		page = page->next;
	}
	//ft_putchar('h');
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
	/*if (size <= TINY)
	{
		ft_putstr("TINY page: ");
		ft_putnbr_n(alloc_length);
	}
	else if (size <= SMALL)
	{
		ft_putstr("SMALL page: ");
		ft_putnbr_n(alloc_length);
	}
	else
	{
		ft_putstr("LARGE page: ");
		ft_putnbr_n(alloc_length);
	}
	*/
	new_block->size = alloc_length;
	new_block->next = *block;
	*block = new_block;
	new_cluster = (void*)new_block + BLOCKSIZE;
	if (size <= SMALL)
		new_cluster->freesize = alloc_length - BLOCKSIZE;
	else
		new_cluster->freesize = LARGE;
	//write(1, "new page\n", 9);
	return (((void*)new_cluster) + CLUSTERSIZE);
}

void		*malloc(size_t size)
{
	//ft_putnbr((int)size);
	//ft_blue(" malloc start\n");
	void	*result;

	size = malloc_good_size(size);
	if (size <= TINY)
	{
		//ft_putchar('a');
		if (!(result = ft_find_cluster(g_alloc.tiny, size)))
		{
			//ft_putchar('b');
			if (ft_new_page(&g_alloc.tiny, TINY))
			{
				//ft_putchar('c');
				result = ft_find_cluster(g_alloc.tiny, size);
			}
		}
	}
	else if (size <= SMALL)
	{
		//ft_putendl("alloc small");
		if (!(result = ft_find_cluster(g_alloc.small, size)))
			if (ft_new_page(&g_alloc.small, SMALL))
				result = ft_find_cluster(g_alloc.small, size);
	}
	else
		result = ft_new_page(&g_alloc.large, size);
	//ft_putaddr(result);
	//ft_putstr(" malloc end allocated: ");
	//ft_putnbr(-((t_cluster*)((void*)result - CLUSTERSIZE))->freesize);
	//ft_putstr(" - 16 = ");
	//ft_putnbr_n(-((t_cluster*)((void*)result - CLUSTERSIZE))->freesize - 16);
	//show_alloc_mem();
	return (result);
}
