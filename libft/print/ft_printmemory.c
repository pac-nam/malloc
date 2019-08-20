/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmemory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:01:45 by tbleuse           #+#    #+#             */
/*   Updated: 2018/11/09 12:14:08 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../header/libft.h"


void		ft_printmemory(void *ptr, int length)
{
	unsigned char	*str;
	char			to_print[length*3];
	char			*base;
	int				i;

	str = (unsigned char*)ptr;
	base = "0123456789ABCDEF";
	i = -1;
	while (++i < length)
	{
		to_print[i*3] = base[str[i] >> 4];
		to_print[i*3+1] = base[str[i] & 0x0F];
		to_print[i*3+2] = ' ';
	}
	write(1, to_print, i * 3 - 1);
}
