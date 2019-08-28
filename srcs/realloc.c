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
/*
void    *ft_ugly_realloc(void *ptr, size_t size)
{
    t_cluster   *cluster;
    void        *new_ptr;

    cluster = ptr - CLUSTERSIZE * 4;
    if (!(new_ptr = ft_malloc(size)))
        return (NULL);
    ft_memcpy(new_ptr, ptr, -cluster->freesize - CLUSTERSIZE);
    ft_free(ptr);
}

void    *ft_realloc_large((t_block*)cluster - 1, size)
{

}

void	*ft_realloc(void *ptr, size_t size)
{
    t_cluster   *cluster;
    int         free

	size = ft_align(size) / 4;
    if (!ptr)
        return ft_malloc(size);
    cluster = ptr - CLUSTERSIZE * 4;
    free = -cluster->freesize - CLUSTERSIZE;
    //printf("ptr: %p\n", cluster);
    //printf("to free size: %d\n", cluster->freesize);
    if (cluster->freesize > 0)
        return ft_malloc(size);
    else if (cluster->freesize == -1 && size > SMALL)
        ft_realloc_large((t_block*)cluster - 1, size);
    else if (TINY < free && free <= SMALL && TINY < size && size <= SMALL)
        ft_realloc_size(&g_alloc.small, cluster, size);
    else if (free <= TINY && size <= TINY)
        ft_realloc_size(&g_alloc.tiny, cluster, size);

}
*/