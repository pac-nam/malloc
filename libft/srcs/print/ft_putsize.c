/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:09:01 by tbleuse           #+#    #+#             */
/*   Updated: 2019/01/10 12:02:56 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
**	print the number nb on the standard output.
*/

void		ft_putsize(size_t nb)
{
	char	str[20];
	size_t	nb2;
	int		len;
	int		len_to_write;
	if (nb < 10)
	{
		str[0] = nb + 48;
		write(1, str, 1);
		return ;
	}
	len = 0;
	nb2 = nb;
	while ((nb2 = nb2 / 10))
		++len;
	len_to_write = len + 1;
	while (nb != 0)
	{
		str[len--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	write(1, str, len_to_write);
}
