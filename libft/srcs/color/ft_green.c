/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_green.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/21/08 13:54:05 by tbleuse           #+#    #+#             */
/*   Updated: 2019/22/08 17:53:19 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "color.h"
#include "str.h"

/*
**	ft_green will write the string passed in green in the standar output.
**	3 syscall have been used to avoid the use of malloc, but it is not
**	optimized.
*/

void	ft_green(char const *s)
{
	if (s)
	{
		write(1, GREEN, ft_strlen(GREEN));
		write(1, s, ft_strlen(s));
		write(1, RESET, ft_strlen(RESET));
	}
}
