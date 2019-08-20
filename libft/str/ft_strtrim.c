/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:07:01 by tbleuse           #+#    #+#             */
/*   Updated: 2018/11/09 14:52:46 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/str.h"

static int	ft_count_char(char const *str)
{
	int		i;
	int		len;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		i++;
	len = ft_strlen(&str[i]);
	i += len - 1;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t') && --len)
		--i;
	return ((len > 0) ? len : 0);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_count_char(s);
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	str[len] = '\0';
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		++i;
	ft_strncpy(str, &s[i], len);
	return (str);
}
