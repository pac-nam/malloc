#include "../header/liballoc.h"

void		*ft_find_cluster(t_block *block, short size)
{
	size_t		space_left;
	t_block		*tmp_block;
	t_cluster	*cluster;

	tmp_block = block;
	while (tmp_block != NULL)
	{
		space_left = tmp_block->size;
		cluster = (void*)tmp_block + BLOCKSIZE;
		while (space_left > (size_t)size)
		{
			if (cluster->freesize >= size)
			{
				if (cluster->freesize != size)
					(cluster + size)->freesize = cluster->freesize - size;
				cluster->freesize = -size;
				return cluster + CLUSTERSIZE;
			}
			space_left -= ft_abs(cluster->freesize);
			cluster += ft_abs(cluster->freesize);
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
	while ((size > SMALL && alloc_length < size + BLOCKSIZE)
	|| (size <= SMALL && alloc_length < 100 * size + 100 * CLUSTERSIZE + BLOCKSIZE))
		alloc_length += PAGESIZE;
	if ((new_block = mmap(0, alloc_length, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->size = alloc_length - BLOCKSIZE;
	new_block->next = block;
	new_cluster = (void*)new_block + BLOCKSIZE;
	new_cluster->freesize = new_block->size;
	if (size <= TINY)
		g_alloc.tiny = new_block;
	else if (size <= SMALL)
		g_alloc.small = new_block;
	else
	{
		g_alloc.large = new_block;
		return (new_block + BLOCKSIZE);
	}
	return (NULL);
}

void		*ft_malloc(size_t size)
{
	void	*result;

	if (size == 0)
		return (NULL);
	else if (size <= TINY)
	{
		if ((result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE)) == NULL)
		{
			ft_new_page(g_alloc.tiny, TINY);
			result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE);
		}
	}
	else if (size <= SMALL)
	{
		if ((result = ft_find_cluster(g_alloc.small, size + CLUSTERSIZE)) == NULL)
		{
			ft_new_page(g_alloc.small, SMALL);
			result = ft_find_cluster(g_alloc.tiny, size + CLUSTERSIZE);
		}
	}
	else
	{
		result = ft_new_page(g_alloc.large, size);
	}
	return (result);
}