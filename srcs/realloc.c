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
    if (cluster->freesize == -1)
        ft_memcpy(new_ptr, ptr,
        ft_smallest(((t_block*)((void*)cluster - BLOCKSIZE))->size, size));
    else
        ft_memcpy(new_ptr, ptr,
        ft_smallest(ft_abs(cluster->freesize) - CLUSTERSIZE, size));
    ft_free(ptr);
    return (new_ptr);
}

void    *ft_realloc_large(t_block *page, size_t size)
{
	t_block		*new_block;

	if (size + BLOCKSIZE + CLUSTERSIZE == page->size)
        return ((void*)page + BLOCKSIZE + CLUSTERSIZE);
	if ((new_block = mmap(0, size + BLOCKSIZE + CLUSTERSIZE,
    PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->size = size + BLOCKSIZE + CLUSTERSIZE;
	new_block->next = g_alloc.large;
    ft_memcpy((void*)new_block + BLOCKSIZE, (void*)page + BLOCKSIZE,
    ft_smallest(page->size - BLOCKSIZE, size + CLUSTERSIZE));
	g_alloc.large = new_block;
    ft_free((void*)page + BLOCKSIZE + CLUSTERSIZE);
    //printf("return realloc large %p\n", (void*)new_block + BLOCKSIZE + CLUSTERSIZE);
	return ((void*)new_block + BLOCKSIZE + CLUSTERSIZE);
}

void    *ft_realloc_size_second(t_cluster *cluster, t_cluster *old_next, int size)
{
    t_cluster   *new_next;

    new_next = (t_cluster*)((void*)cluster + size + CLUSTERSIZE);
    if (size + 2 * (int)CLUSTERSIZE <= -cluster->freesize)
    {
        new_next->freesize = ft_abs(cluster->freesize) - (size + CLUSTERSIZE);
        if (old_next->freesize > 0)
            new_next->freesize += old_next->freesize;
        cluster->freesize = -(size + CLUSTERSIZE);
        return ((void*)cluster + CLUSTERSIZE);
    }
    if (old_next->freesize < 0 || ft_abs(cluster->freesize) + old_next->freesize
    < size + 2 * (int)CLUSTERSIZE)
        return ft_ugly_realloc((void*)cluster + CLUSTERSIZE, size);
    //printf("cluster %p\n", cluster);
    //printf("freesize %d\n", cluster->freesize);
    //printf("asked %d\n", size + (int)CLUSTERSIZE);
    //printf("bzero size %d\n", size - ft_abs(cluster->freesize));
    if (size + (int)CLUSTERSIZE > -cluster->freesize)
        ft_bzero((void*)cluster + ft_abs(cluster->freesize), size
        - ft_abs(cluster->freesize));
    //printf("BALISE b\n");
    new_next->freesize = old_next->freesize - ((size + CLUSTERSIZE)
    - ft_abs(cluster->freesize));
    //printf("BALISE c\n");
    cluster->freesize = -(size + CLUSTERSIZE);
    //printf("BALISE d\n");
    return ((void*)cluster + CLUSTERSIZE);
}

void    *ft_realloc_size(t_cluster *cluster, int size)
{
    t_cluster   *old_next;
    void        *to_return;

    //printf("BALISE1\n");
    old_next = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
    if (size + (int)CLUSTERSIZE == -cluster->freesize)
        to_return = ((void*)cluster + CLUSTERSIZE);
    else if (old_next->freesize > 0 && size + (int)CLUSTERSIZE
    == -cluster->freesize + old_next->freesize)
    {
        cluster->freesize = cluster->freesize - old_next->freesize;
        ft_bzero((void*)old_next, old_next->freesize);
        to_return = ((void*)cluster + CLUSTERSIZE);
    }
    else
        to_return = (ft_realloc_size_second(cluster, old_next, size));
    //printf("BALISE2\n");
    return (to_return);
}

void	*ft_realloc(void *ptr, size_t size)
{
    //printf("BALISE3\n");
    t_cluster   *cluster;
    int         free;
    void        *to_return;

	size = ft_align(size);
    if (!ptr)
        return ft_malloc(size);
    cluster = (t_cluster*)(ptr - CLUSTERSIZE);
    free = ft_abs(cluster->freesize) - CLUSTERSIZE;
    //printf("\nrealloc ptr: %p\n", ptr);
    //printf("to realloc size: %ld\n", size);
    //printf("actual size: %d\n", cluster->freesize);
    if (cluster->freesize > 0)
        to_return = ft_malloc(size);
    else if (cluster->freesize == -1 && size > SMALL)
        to_return = ft_realloc_large((t_block*)((void*)cluster - BLOCKSIZE), size);
    else if (TINY < free && free <= SMALL && TINY < size && size <= SMALL)
        to_return = ft_realloc_size(cluster, size);
    else if (free <= TINY && size <= TINY)
        to_return = ft_realloc_size(cluster, size);
    else
        to_return = ft_ugly_realloc(ptr, size);
    //printf("BALISE4\n");
    return (to_return);
}
