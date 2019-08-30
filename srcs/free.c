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

void    ft_free_in_this_page(t_cluster *prev, t_cluster *to_remove)
{
    t_cluster   *cluster;

    cluster = (void*)prev + ft_abs(prev->freesize);
    if (to_remove == prev)
    {
        prev->freesize = -prev->freesize;
        if (cluster->freesize > 0)
            prev->freesize += cluster->freesize;
        return ;
    }
    while (cluster < to_remove)
    {
        prev = cluster;
        cluster = (void*)cluster + ft_abs(cluster->freesize);
    }
    cluster = (void*)cluster + ft_abs(cluster->freesize);
    to_remove->freesize = -to_remove->freesize;
    if (cluster->freesize > 0)
        to_remove->freesize += cluster->freesize;
    if (prev->freesize > 0)
        prev->freesize += to_remove->freesize;
}

void    ft_free_in_first_page(t_block **page, void *to_remove)
{
    t_cluster   *cluster;
    t_block     *current;

    ft_free_in_this_page((void*)*page + BLOCKSIZE, to_remove);
    cluster = (t_cluster*)((void*)(*page) + BLOCKSIZE);
    if (cluster->freesize == (int)((*page)->size - BLOCKSIZE))
    {
        current = *page;
        *page = (*page)->next;
        munmap(current, current->size);
    }
}

void    ft_free_size(t_block **page, void *to_remove)
{
    t_block     *prev;
    t_block     *current;
    t_cluster   *cluster;

    prev = *page;
    if ((void*)prev < to_remove && to_remove <= (void*)prev + prev->size)
        ft_free_in_first_page(page, to_remove);
    else
    {
        while ((current = prev->next))
        {
            if ((void*)current < to_remove
            && to_remove <= (void*)current + current->size)
            {
                ft_free_in_this_page((void*)current + BLOCKSIZE, to_remove);
                cluster = (t_cluster*)((void*)current + BLOCKSIZE);
                if (cluster->freesize == (int)(current->size - BLOCKSIZE))
                {
                    prev->next = current->next;
                    munmap(current, current->size);
                }
                return ;
            }
            prev = current;
        }
    }
}

void    ft_free_large(t_block  *ptr)
{
    t_block    *tmp;

    if (ptr == g_alloc.large)
    {
        //ft_putendl("first to remove");
        g_alloc.large = g_alloc.large->next;
        munmap(ptr, ptr->size);
        return ;
    }
    tmp = g_alloc.large;
    while (tmp->next)
    {
        //printf("\nptr: %p\n", ptr);
        //printf("tmp: %p\n", tmp);
        if (tmp->next == ptr)
        {
            tmp->next = tmp->next->next;
            munmap(ptr, ptr->size);
            return ;
        }
        tmp = tmp->next;
    }
}

void	ft_free(void *ptr)
{
    t_cluster   *cluster;

    if (!ptr)
        return ;
    cluster = ptr - CLUSTERSIZE;
    //printf("ptr to free: %p\n", ptr);
    //printf("to free size: %d\n", cluster->freesize);
    if (cluster->freesize > 0)
        return ;
    else if (cluster->freesize == -1)
        ft_free_large((t_block*)cluster - 1);
    else if (-cluster->freesize - CLUSTERSIZE <= TINY)
        ft_free_size(&g_alloc.tiny, cluster);
    else if (-cluster->freesize - CLUSTERSIZE <= SMALL)
        ft_free_size(&g_alloc.small, cluster);
}