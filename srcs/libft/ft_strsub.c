/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 04:57:22 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/08 23:33:10 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, size_t start, size_t len, size_t freeit)
{
	char		*new;
	const char	*tmp;

	tmp = s;
	if (!s || !(new = ft_strnew(len)))
		return (NULL);
	while (start--)
		s++;
	ft_strncpy(new, s, len);
	new[len] = '\0';
	if (freeit == 1)
		free((char*)tmp);
	return (new);
}
