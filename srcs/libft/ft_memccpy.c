/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:04:25 by bsiche            #+#    #+#             */
/*   Updated: 2017/12/01 15:02:19 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	str = (unsigned char*)src;
	while (i < n)
	{
		((unsigned char*)dest)[i] = str[i];
		if (str[i] == c2)
		{
			i++;
			return (dest + i);
		}
		i++;
	}
	return (NULL);
}
