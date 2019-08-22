/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_magenta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
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