#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "includes/liballoc.h"

//printf("page size:%p\n", mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));

int		main(void)
{
	printf("BLOCKSIZE %ld\n", BLOCKSIZE);
	printf("CLUSTERSIZE %ld\n", CLUSTERSIZE);
	printf("PAGESIZE %d\n", PAGESIZE);
/*	char	*ptr1;
	char	*ptr2;
	char	*ptr3;
	char	*ptr4;
	char	*ptr5;
	char	*ptr6;
	char	*ptr7;
	char	*ptr8;
	char	*ptr9;

	printf("PAGESIZE %d\n\nptr1\n", PAGESIZE);
	ptr1 = ft_malloc(10);
	printf("\tfinal address: %p\nptr2\n", ptr1);
	ptr2 = ft_malloc(10);
	printf("\tfinal address: %p\nptr3\n", ptr2);
	ptr3 = ft_malloc(10);
	printf("\tfinal address: %p\nptr4\n", ptr3);
	ptr4 = ft_malloc(100);
	printf("\tfinal address: %p\nptr5\n", ptr4);
	ptr5 = ft_malloc(100);
	printf("\tfinal address: %p\nptr6\n", ptr5);
	ptr6 = ft_malloc(100);
	printf("\tfinal address: %p\nptr7\n", ptr6);
	ptr7 = ft_malloc(1000);
	printf("\tfinal address: %p\nptr8\n", ptr7);
	ptr8 = ft_malloc(1000);
	printf("\tfinal address: %p\nptr9\n", ptr8);
	ptr9 = ft_malloc(1000);
	printf("\tfinal address: %p\n", ptr9);
	printf("tiny %p\n", g_alloc.tiny);
	printf("small %p\n", g_alloc.small);
	printf("large %p\n", g_alloc.large);
*/

/*
	void	*leaks;
	int		i = 0;

	printf("sizeof(t_block): %ld\n", BLOCKSIZE);
	printf("sizeof(t_cluster): %ld\n", CLUSTERSIZE);
	printf("leaks first:\n");
	while (i++ < 3000) {
		leaks = ft_malloc(50);
		printf("\tfinal address: %p\nleaks %d:\n", leaks, i);
		if (leaks == NULL)
			break;
	}
*/
/*
	for (int i = 0; i < 3; i++)
	{
		ft_malloc(10);
		ft_malloc(100 + i % 100);
		ft_malloc(4064);
	}
	ft_show_alloc_mem();
*/

	int		nb = 2;
	void	*free_it[nb*3];
	ft_putendl("BEFORE EVRYTHING");
	ft_show_alloc_mem();
	for (int i = 0; i < nb; i++)
	{
		free_it[i] = ft_malloc(21);
		ft_memset(free_it[i], 5434, 21);
		free_it[nb+i] = ft_malloc(150);
		free_it[nb*2+i] = ft_malloc(500);
	}
	ft_putendl("AFTER MALLOCS");
	ft_show_alloc_mem();
	for (int i = 0; i < nb; i++)
	{
		//if (i == 0)
		//	free_it[i] = ft_realloc(free_it[i], 33);
		//else
			free_it[i] = ft_realloc(free_it[i], 13);
		ft_memset(free_it[i], 12341, 13);
		free_it[nb+i] = ft_realloc(free_it[nb+i], 200);
		free_it[nb*2+i] = ft_realloc(free_it[nb*2+i], 3000);
	//ft_putendl("----------------------------------------------------");
	//ft_show_alloc_mem();
	}
	ft_putendl("AFTER REALLOCS");
	ft_show_alloc_mem();
	for (int i = 0; i < nb; i++)
	{
		ft_free(free_it[i]);
		ft_free(free_it[nb+i]);
		ft_free(free_it[nb*2+i]);
	}
	ft_putendl("AFTER FREES");
	ft_show_alloc_mem();



































return (0);
}
