#include "../header/liballoc.h"

t_cluster	*ft_new_cluster(t_cluster *first, t_cluster *new_start, void *start, void *end)
{
	new_start->start = start;
	new_start->end = end;
	new_start->next = first;
	return (new_start);
}

void		*ft_new_zone(t_zone *zone, t_zone *new_zone, size_t size)
{
	size_t		multiplier;
	t_cluster	new_cluster;
	
	printf("BALISE1 %ld\n", size);

	while (++multiplier * PAGESIZE / size < 100 && size <= SMALL)
		;
	if ((new_zone->start = mmap(NULL, multiplier * PAGESIZE, PROT_READ
	| PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return NULL;
	new_zone->length = multiplier * PAGESIZE;
	new_zone->vacant = NULL;
	if (size <= SMALL)
		new_zone->vacant = ft_new_cluster(new_zone->vacant, &new_cluster,
		new_zone->start + size, new_zone->start + new_zone->length);
	new_zone->used = 1;
	new_zone->next = zone;
	if (size <= TINY)
		g_alloc.tiny = new_zone;
	else if (size <= SMALL)
		g_alloc.small = new_zone;
	else
		g_alloc.large = new_zone;
	return (new_zone);
}

void		*ft_find_cluster(t_zone *zone, int size)
{
	t_zone		*tmp_zone;
	t_cluster	*tmp_cluster;
	void		*result;

	tmp_zone = zone;
	while (tmp_zone != NULL)
	{
		if (tmp_zone->vacant != NULL)
		{
			result = tmp_zone->vacant->start;
			tmp_zone->vacant->start += size;
			if (tmp_zone->vacant->start == tmp_zone->vacant->end)
				tmp_zone->vacant = tmp_zone->vacant->next;
			tmp_zone->used++;
			return result;
		}
		tmp_zone = tmp_zone->next;
	}
	return (NULL);
}

void		*ft_malloc(size_t size)
{
	void	*result;
	t_zone	new_zone;

	if (size == 0)
		return (NULL);
	else if (size <= TINY)
		if ((result = ft_find_cluster(g_alloc.tiny, TINY)) == NULL)
			result = ft_new_zone(g_alloc.tiny, &new_zone, TINY);
	else if (size <= SMALL)
		if ((result = ft_find_cluster(g_alloc.small, SMALL)) == NULL)
			result = ft_new_zone(g_alloc.small, &new_zone, SMALL);
	else
		result = ft_new_zone(g_alloc.large, &new_zone, size);
	return (result);
}