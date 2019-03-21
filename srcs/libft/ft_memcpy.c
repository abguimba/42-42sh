/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:04:25 by bsiche            #+#    #+#             */
/*   Updated: 2017/12/01 15:01:34 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char*)src;
	while (i < n)
	{
		((char*)dest)[i] = str[i];
		i++;
	}
	return (dest);
}
