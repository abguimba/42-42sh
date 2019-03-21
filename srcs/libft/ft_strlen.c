/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:57:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/10 19:03:50 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	if (s == NULL)
		return (0);
	str = (unsigned char *)s;
	while (str[i])
		i++;
	return (i);
}
