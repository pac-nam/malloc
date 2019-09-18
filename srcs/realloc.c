///* ************************************************************************** */
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
    size_t      largesize;

    if (!ft_check_ptr(ft_get_malloc_page(ptr), ptr))
        return (NULL);
    cluster = (void*)ptr - CLUSTERSIZE;
    if (!(new_ptr = malloc(size)))
        return (NULL);
    if (cluster->freesize == LARGE)
    {
        //ft_putendl("hello world");
        largesize = ((t_block*)((void*)cluster - BLOCKSIZE))->size - BLOCKSIZE - CLUSTERSIZE;
        ft_memcpy(new_ptr, ptr, (largesize < size) ? largesize : size);
    }
    else
        ft_memcpy(new_ptr, ptr, (ft_abs(cluster->freesize) - CLUSTERSIZE < size)
        ? ft_abs(cluster->freesize) - CLUSTERSIZE : size);
    free(ptr);
    return (new_ptr);
}

void    *realloc_size(t_block* page, t_cluster *to_realloc, int size)
{
    t_cluster   *old_next;
    t_cluster   *new_next;
    t_cluster   *cluster;

    if (-to_realloc->freesize == size)
    {
        return ((void*)to_realloc + CLUSTERSIZE);
    }
    cluster = (t_cluster*)((void*)page + BLOCKSIZE);
    while (cluster < to_realloc)
        cluster = (void*)cluster + ft_abs(cluster->freesize);
    if (cluster != to_realloc)
        return (NULL);
    old_next = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
    new_next = (t_cluster*)((void*)cluster + size);
    if (size < -cluster->freesize)
    {
        new_next->freesize = (-cluster->freesize) - size;
        cluster->freesize = -size;
    }
    else if (size > -cluster->freesize)
    {
        if ((int)((-cluster->freesize) + old_next->freesize) > size)
        {
            if ((int)((-cluster->freesize) + old_next->freesize) != size)
                new_next->freesize = ((-cluster->freesize) + old_next->freesize) - size;
            cluster->freesize = -size;
            old_next->freesize = 0;
        }
        else
            return (ft_ugly_realloc(((void*)to_realloc) + CLUSTERSIZE, size - CLUSTERSIZE));
    }
    return ((void*)cluster + CLUSTERSIZE);
}

void	*realloc(void *ptr, size_t size)
{
    //ft_putaddr(ptr);
	//ft_yellow(" to realloc size ");
    //ft_putnbr_n(size);
    t_cluster   *cluster;
    int         freesize;
    void        *to_return;
    t_block     *page;

    to_return = NULL;
    if (!ptr || (ptr && !size))
    {
        to_return = malloc(malloc_good_size(size));
        free(ptr);
    }
    else if ((page = ft_get_malloc_page(ptr)))
    {
        size = malloc_good_size(size);
        cluster = (t_cluster*)(ptr - CLUSTERSIZE);
        freesize = ft_abs(cluster->freesize) - CLUSTERSIZE;
        //ft_putstr("freesize: ");
        //ft_putnbr_n(freesize);
        if (cluster->freesize > 0)
            to_return = malloc(size);
        else if (cluster->freesize == LARGE && size > SMALL
        && page->size == size + BLOCKSIZE + CLUSTERSIZE)
            return (ptr);
        else if (TINY < freesize && freesize <= SMALL && TINY < size && size <= SMALL)
            to_return = realloc_size(page, cluster, size + CLUSTERSIZE);
        else if (freesize <= TINY && size <= TINY)
            to_return = realloc_size(page, cluster, size + CLUSTERSIZE);
        else
        {
            //ft_putendl("ugly realloc");
            to_return = ft_ugly_realloc(ptr, size);
        }
    }
    //ft_putaddr(to_return);
	//ft_putstr(" realloked size: ");
    //ft_putnbr_n(-((t_cluster*)(to_return - CLUSTERSIZE))->freesize - 16);
    //show_alloc_mem();
    return (to_return);
}
