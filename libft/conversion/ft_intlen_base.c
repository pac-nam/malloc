/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 10:41:34 by exam              #+#    #+#             */
/*   Updated: 2018/03/21 13:56:59 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_intlen_base(int value, int base)
{
	int	len;

	len = 0;
	if ((value < 0 && base != 10) || base < 2)
		return (0);
	if (value == 0)
		return (1);
	if (value < 0)
		len++;
	while (value > 0)
	{
		value = value / base;
		len++;
	}
	return (len);
}
