/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubuntilchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 01:37:07 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/05 15:23:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubuntilchar(const char *str, size_t start, char end_char)
{
	char	*newstring;
	size_t	i;

	newstring = ft_strnew(0);
	i = start;
	while (str[i] != end_char || str[i])
	{
		newstring = ft_strjoinfree(newstring, ft_strsub(str, i, i + 1, 0), 1);
		i++;
	}
	return (newstring);
}
