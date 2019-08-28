/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liballoc.h"

void    ft_print_cluster(t_cluster *cluster)
{
    ft_putstr("\t\t");
    ft_putaddr((void*)cluster + CLUSTERSIZE);
    ft_putstr(" - ");
    //ft_putstr("|debug ");
    //ft_putnbr(ft_abs(cluster->freesize));
    //ft_putstr(" |");
    ft_putaddr((void*)cluster + ft_abs(cluster->freesize));
    ft_putstr(" ");
    ft_putnbr(ft_abs(cluster->freesize) - CLUSTERSIZE);
    if (cluster->freesize < 0)
        ft_putstr(" used\n");
    else if (cluster->freesize > 0)
        ft_putstr(" free\n");
}

void    ft_print_pages(t_block *page)
{
    int         page_number;
    t_cluster   *tmp_cluster;
    t_block     *tmp_page;

    page_number = 0;
    tmp_page = page;
    while (tmp_page)
    {
        ft_putstr("\n\tPAGE ");
        ft_putnbr(++page_number);
        ft_putstr("  ");
        ft_putaddr(tmp_page);
        ft_putstr(" - ");
        ft_putaddr((void*)tmp_page + tmp_page->size);
        ft_putstr(" ");
        ft_putnbr(tmp_page->size);
        ft_putstr(" octets\n");
        tmp_cluster = (void*)tmp_page + BLOCKSIZE;
        while ((void*)tmp_cluster < (void*)tmp_page + tmp_page->size)
        {
            ft_print_cluster(tmp_cluster);
            tmp_cluster = (void*)tmp_cluster + ft_abs(tmp_cluster->freesize);
        }
        tmp_page = tmp_page->next;
    }
}

void	ft_show_alloc_mem(void)
{
    t_block     *tmp_page;

    ft_magenta("TINY:");
    ft_print_pages(g_alloc.tiny);
    ft_magenta("\nSMALL:");
    ft_print_pages(g_alloc.small);
    ft_magenta("\nLARGES:\n");
    tmp_page = g_alloc.large;
    while (tmp_page)
    {
        ft_putstr("\t");
        ft_putaddr((void*)tmp_page + CLUSTERSIZE + BLOCKSIZE);
        ft_putstr(" - ");
        ft_putaddr((void*)tmp_page + tmp_page->size);
        ft_putstr(" ");
        ft_putnbr(tmp_page->size - CLUSTERSIZE - BLOCKSIZE);
        ft_putstr(" octets\n");
        tmp_page = tmp_page->next;
    }
}