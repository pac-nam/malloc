#include "../header/liballoc.h"

void ft_print_var(const char* str, size_t nb)
{
    ft_putstr(str);
    ft_putnbr_n(nb);
}

void    ft_putaddr(void *ptr)
{
    unsigned long long  cpy;
    int                 index;
    char                str[16];

    cpy = (unsigned long)ptr;
    str[0] = '0';
    str[1] = 'x';
    index = 14;
    while (--index > 1)
    {
        str[index] = (cpy % 16) + '0';
        if (str[index] > '9')
            str[index] += 39;
        cpy = cpy / 16;
    }
    write(1, str, 14);
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
        ft_print_var("\n\tPAGE ", ++page_number);
        ft_print_var("\tsize: ", tmp_page->size + BLOCKSIZE);
        tmp_cluster = (void*)tmp_page + BLOCKSIZE;
        while ((void*)tmp_cluster < (void*)tmp_page + tmp_page->size + BLOCKSIZE)
        {
            ft_putstr("\t\t");
            ft_putaddr(tmp_cluster);
            if (tmp_cluster->freesize < 0)
                ft_print_var(" used: ", -tmp_cluster->freesize);
            else if (tmp_cluster->freesize > 0)
                ft_print_var(" free: ", tmp_cluster->freesize);
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
        ft_print_var("\n\tPAGE ", ++page_number);
        ft_putstr("\t\t");
        ft_putaddr(tmp_page + BLOCKSIZE);
        ft_print_var(" size: ", tmp_page->size);
        tmp_page = tmp_page->next;
    }
    ft_putstr("\n");
}