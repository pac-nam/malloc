/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_magenta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 10:27:59 by tbleuse           #+#    #+#             */
/*   Updated: 2018/03/21 14:24:41 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../header/colors.h"
#include "../header/str.h"

void	ft_magenta(char const *s)
{
	if (s)
	{
		write(1, MAGENTA, ft_strlen(MAGENTA));
		write(1, s, ft_strlen(s));
		write(1, RESET, ft_strlen(RESET));
	}
}