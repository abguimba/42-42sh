/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 21:41:22 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:40:27 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_subtime(char *dup, char *tmp)
{
	char	*tmp2;

	tmp = ft_strsub(dup, 4, 7, 2);
	tmp2 = ft_strsub(dup, 20, 4, 1);
	tmp2 = ft_strjoinfree(" ", tmp2, 2);
	tmp = ft_strjoinfree(tmp, tmp2, 3);
	return (tmp);
}

char	*getblank(size_t j, size_t k)
{
	char	*buf;

	buf = ft_strnew(j);
	while (k < j)
	{
		buf[k] = ' ';
		k++;
	}
	return (buf);
}

int		getspacesize(t_list *liste)
{
	size_t maxsize;
	size_t maxmaj;

	maxsize = ft_getmaxlen(liste, 1, 0);
	maxmaj = ft_getidlen(liste, 0) + 1;
	if (maxmaj > maxsize)
		return (maxmaj);
	else
		return (maxsize);
}
