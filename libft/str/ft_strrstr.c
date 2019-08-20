/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:35:32 by tbleuse           #+#    #+#             */
/*   Updated: 2018/11/09 13:28:55 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/str.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	int				i;
	int				j;
	int				save;

	if (!needle[0])
		return ((char*)haystack);
	i = ft_strlen(haystack) - ft_strlen(needle) - 1;
	save = 0;
	while (i > -2)
	{
		j = -1;
		while (haystack[++i] == needle[++j])
			if (!needle[j + 1])
				return ((char*)&haystack[save]);
		i = --save - 1;
	}
	return (NULL);
}
