/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:03:01 by alsomvil          #+#    #+#             */
/*   Updated: 2018/01/13 05:13:35 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *)s1;
	while (s1[i] && i < n)
		i++;
	if (!s1[i])
		return (ft_strdup(s1));
	if (!(temp = ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		temp[i] = s1[i];
		i++;
	}
	return (temp);
}
