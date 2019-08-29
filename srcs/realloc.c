/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "liballoc.h"

void    *ft_ugly_realloc(void *ptr, size_t size)
{
    t_cluster   *cluster;
    void        *new_ptr;

    cluster = (void*)ptr - CLUSTERSIZE;
    if (!(new_ptr = ft_malloc(size)))
        return (NULL);
    ft_memcpy(new_ptr, ptr, -cluster->freesize - CLUSTERSIZE);
    ft_free(ptr);
    return (new_ptr);
}

void    *ft_realloc_large(t_block *page, size_t size)
{
	size_t		alloc_length;
	t_block		*new_block;

	alloc_length = PAGESIZE;
    while (alloc_length < size + CLUSTERSIZE + BLOCKSIZE)
		alloc_length += PAGESIZE;
	if (alloc_length == page->size)
        return ((void*)page + BLOCKSIZE + CLUSTERSIZE);
	if ((new_block = mmap(0, alloc_length, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->size = alloc_length;
	new_block->next = g_alloc.large;
    ft_memcpy((void*)new_block + BLOCKSIZE, (void*)page + BLOCKSIZE,
    page->size - BLOCKSIZE);
	g_alloc.large = new_block;
    ft_free((void*)page + BLOCKSIZE + CLUSTERSIZE);
    //printf("return realloc large %p\n", (void*)new_block + BLOCKSIZE + CLUSTERSIZE);
	return ((void*)new_block + BLOCKSIZE + CLUSTERSIZE);
}
void    *ft_realloc_size(t_cluster *cluster, int size)
{
    t_cluster   *old_next;
    t_cluster   *new_next;
    
    //printf("realloc cluster %p freesize %d\n", cluster, cluster->freesize);
    if (size + (int)CLUSTERSIZE <= -cluster->freesize)
        return ((void*)cluster + CLUSTERSIZE);
    old_next = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
    if (ft_abs(cluster->freesize) + old_next->freesize < size + 2 * (int)CLUSTERSIZE)
        return ft_ugly_realloc((void*)cluster + CLUSTERSIZE, size);
    new_next = (t_cluster*)((void*)cluster + size + CLUSTERSIZE);
    //printf("\ncluster %p\n", cluster);
    //printf("old_next %p\n", old_next);
    //printf("new_next %p\n", new_next);
    //printf("size %d\n", size);
    //printf("ft_abs(cluster->freesize) %d\n", ft_abs(cluster->freesize));
    new_next->freesize = old_next->freesize - ((size + CLUSTERSIZE) - ft_abs(cluster->freesize));
    //printf("new_next->freesize %d\n", new_next->freesize);
    ft_bzero((void*)cluster + ft_abs(cluster->freesize), size - ft_abs(cluster->freesize));
    cluster->freesize = -(size + CLUSTERSIZE);
    //printf("new cluster->freesize %d\n", cluster->freesize);
    return ((void*)cluster + CLUSTERSIZE);
}

void	*ft_realloc(void *ptr, size_t size)
{
    t_cluster   *cluster;
    int         free;

	size = ft_align(size);
    if (!ptr)
        return ft_malloc(size);
    cluster = (t_cluster*)(ptr - CLUSTERSIZE);
    free = ft_abs(cluster->freesize) - CLUSTERSIZE;
    //printf("\nrealloc ptr: %p\n", ptr);
    //printf("to realloc size: %ld\n", size);
    //printf("actual size: %d\n", cluster->freesize);
    if (cluster->freesize > 0)
        return ft_malloc(size);
    else if (cluster->freesize == -1 && size > SMALL)
        return ft_realloc_large((t_block*)((void*)cluster - BLOCKSIZE), size);
    else if (TINY < free && free <= SMALL && TINY < size && size <= SMALL)
        return ft_realloc_size(cluster, size);
    else if (free <= TINY && size <= TINY)
        return ft_realloc_size(cluster, size);
    else
        return ft_ugly_realloc(ptr, size);
}
