/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:59:49 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/15 03:21:52 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if ((str = ft_malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	ft_memcpy(str, s, i);
	str[i++] = '\0';
	return (str);
}

int		is_car(char c)
{
	if (c == '\t' || c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}

char	*ft_strdup_nocar(const char *s)
{
	char	*str;
	int		i;
	int		a;

	if (!s)
		return (NULL);
	a = 0;
	i = ft_strlen(s);
	if (!(str = ft_strnew(i + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (is_car(s[i]) == 0)
		{
			str[a] = s[i];
			a++;
		}
		i++;
	}
	return (str);
}

char	*ft_strdupfree(char *s)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s);
	if ((str = ft_malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	ft_memcpy(str, s, i);
	str[i++] = '\0';
	ft_free(s);
	return (str);
}
