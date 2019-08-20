#include "../header/liballoc.h"

void    ft_print_var(const char* str, size_t nb)
{
    ft_putstr(str);
    ft_putnbr_n(nb);
}

void    ft_print_cluster(t_cluster *cluster)
{
    ft_putstr("\t\t");
    ft_putaddr(cluster + CLUSTERSIZE);
    ft_putstr(" - ");
    ft_putaddr(cluster + ft_abs(cluster->freesize));
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
        ft_putstr(" ");
        ft_putaddr(tmp_page);
        ft_putstr(" ");
        ft_putnbr(tmp_page->size + BLOCKSIZE);
        ft_putstr(" octets\n");
        tmp_cluster = (void*)tmp_page + BLOCKSIZE;
        while ((void*)tmp_cluster < (void*)tmp_page + tmp_page->size + BLOCKSIZE)
        {
            ft_print_cluster(tmp_cluster);
            tmp_cluster += ft_abs(tmp_cluster->freesize);
        }
        tmp_page = tmp_page->next;
    }
}

void	ft_show_alloc_mem(void)
{
    int         page_number;
    t_block     *tmp_page;

    ft_putstr("TINY:");
    ft_print_pages(g_alloc.tiny);
    ft_putstr("\nSMALL:");
    ft_print_pages(g_alloc.small);
    ft_putstr("\nLARGES:");
    tmp_page = g_alloc.large;
    page_number = 0;
    while (tmp_page)
    {
        ft_putstr("\n\tPAGE ");
        ft_putnbr(++page_number);
        ft_putstr(" ");
        ft_putaddr(tmp_page + BLOCKSIZE);
        ft_putstr(" - ");
        ft_putaddr(tmp_page + tmp_page->size + BLOCKSIZE);
        ft_putstr(" ");
        ft_putnbr(tmp_page->size);
        ft_putstr(" octets\n");
        tmp_page = tmp_page->next;
    }
    ft_putstr("\n");
}