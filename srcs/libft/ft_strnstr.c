/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:49:25 by bsiche            #+#    #+#             */
/*   Updated: 2017/12/01 17:26:48 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	while (haystack[i])
	{
		while (needle[j] == haystack[i] && i < n)
		{
			i++;
			j++;
			if (needle[j] == '\0')
				return (((char*)haystack) + i - ft_strlen(needle));
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (NULL);
}
