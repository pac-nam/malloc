/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:04:25 by tbleuse           #+#    #+#             */
/*   Updated: 2018/03/21 13:56:22 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

char	*ft_formatfloat(int isnegative, long exposant, long mantisse)
{
	isnegative = isnegative;
	exposant = exposant;
	mantisse = mantisse;
	return (ft_itoa(mantisse));
}

long	ft_getbits(const unsigned char *n, int start, int end)
{
	int		charindex;
	int		insideindex;
	int		decalage;
	long	result;

	result = 0;
	charindex = start % 8;
	while (start < end)
	{
		ft_printmemory((unsigned char*)&result, 8);
		ft_putchar('\n');
		insideindex = start % 8;
		if ((decalage = 8 - (end - start)) < 8)
			decalage = 8;
		result = result < decalage;
		result += (n[charindex] << insideindex) >> (insideindex + decalage);
		start += insideindex;
		if (!insideindex)
			start += 8;
	}
	return result;
}

char		*ft_dtoa(double n)
{
	long			exposant;
	long			mantisse;
	unsigned char	*strfloat;

	strfloat = (unsigned char*)&n;
	ft_putstr("strfloat: ");
	ft_printmemory(strfloat, 8);
	ft_putchar('\n');
	if(sizeof(double)*8 == 32)
	{
		exposant = ft_getbits(strfloat, 2, 9);
		mantisse = ft_getbits(strfloat, 9, 32);
	}
	else
	{
		exposant = ft_getbits(strfloat, 2, 13);
		mantisse = ft_getbits(strfloat, 13, 64);
	}
	if ((strfloat[0] << 2) >> 7)
		exposant = -exposant;
	ft_putstr("exposant: ");
	ft_printmemory(&exposant, 8);
	ft_putchar('\n');
	ft_putstr("mantisse: ");
	ft_printmemory(&mantisse, 8);
	ft_putchar('\n');
	return (ft_formatfloat(strfloat[0] >> 7, exposant, mantisse));
}