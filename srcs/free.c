/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liballoc.h"

int         ft_check_ptr(t_block *page, void *to_find)
{
    t_cluster   *cluster;

    //ft_putendl("BALISE 1");
    if (!page || !to_find)
        return (0);
    //ft_putendl("BALISE 2");
    cluster = (t_cluster*)((void*)page + BLOCKSIZE);
    while ((void*)cluster + CLUSTERSIZE < to_find)
        cluster = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
    //ft_putendl("BALISE 3");
    if ((void*)cluster + CLUSTERSIZE == to_find)
        return (1);
    //ft_putendl("BALISE 4");
    return (0);
}

t_block     *ft_get_malloc_page(void *ptr)
{
    t_block     *tmp;

    if (!ptr)
        return (NULL);
    tmp = g_alloc.tiny;
    while (tmp)
        if ((void*)tmp < ptr && ptr < (void*)tmp + tmp->size
        && ft_check_ptr(tmp, ptr))
            return(tmp);
        else 
            tmp = tmp->next;
    tmp = g_alloc.small;
    while (tmp)
        if ((void*)tmp < ptr && ptr < (void*)tmp + tmp->size
        && ft_check_ptr(tmp, ptr))
            return(tmp);
        else 
            tmp = tmp->next;
    tmp = g_alloc.large;
    while (tmp)
        if ((void*)tmp + BLOCKSIZE + CLUSTERSIZE == ptr)
            return(tmp);
        else
            tmp = tmp->next;
    return (NULL);
}

void    ft_free_page(t_block  **start, t_block *to_free)
{
    t_block    *tmp;

    if (to_free == *start)
    {
        *start = to_free->next;
        munmap(to_free, to_free->size);
        return ;
    }
    tmp = *start;
    while (tmp->next)
    {
        if (tmp->next == to_free)
        {
            tmp->next = tmp->next->next;
            munmap(to_free, to_free->size);
            return ;
        }
        tmp = tmp->next;
    }
}

void    free_cluster(t_block **start, t_block *page, void *to_free)
{
    t_cluster   *cluster;
    t_cluster   *cluster_next;
    t_cluster   *cluster_next2;

    cluster = (void*)page + BLOCKSIZE;
    cluster_next = (t_cluster*)((void*)cluster + ft_abs(cluster->freesize));
    if ((void*)cluster == to_free)
    {
        cluster->freesize = -cluster->freesize;
        if (cluster_next->freesize > 0)
            cluster->freesize += cluster_next->freesize;
    }
    else
    {
        while ((void*)cluster_next < (void*)page + page->size)
        {
            if ((void*)cluster_next == to_free)
            {
                cluster_next->freesize = -cluster_next->freesize;
                cluster_next2 = (t_cluster*)((void*)cluster_next + cluster_next->freesize);
                if (cluster_next2->freesize > 0)
                    cluster_next->freesize += cluster_next2->freesize;
                if (cluster->freesize > 0)
                    cluster->freesize += cluster_next->freesize;
            }
            cluster = cluster_next;
            cluster_next = (t_cluster*)((void*)cluster_next + ft_abs(cluster_next->freesize));
        }
    }
    if (((t_cluster*)((void*)page + BLOCKSIZE))->freesize == (int)(page->size - BLOCKSIZE))
        ft_free_page(start, page);
}

void	free(void *ptr)
{
    ft_putaddr(ptr);
	ft_green(" to free\n");
    t_block *page;
    t_cluster   *cluster;

    if ((page = ft_get_malloc_page(ptr)))
    {
        cluster = ptr - CLUSTERSIZE;
        if (cluster->freesize > 0)
            ;
        else if (cluster->freesize == -1)
        {
            ft_free_page(&g_alloc.large, page);
        }
        else if (-cluster->freesize - CLUSTERSIZE <= TINY)
        {
            free_cluster(&g_alloc.tiny, page, cluster);
        }
        else if (-cluster->freesize - CLUSTERSIZE <= SMALL)
        {
            free_cluster(&g_alloc.small, page, cluster);
        }
    }
	ft_putendl("free end");
    //show_alloc_mem();
}
