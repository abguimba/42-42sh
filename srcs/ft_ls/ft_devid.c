/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_devid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:08:12 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

size_t	ft_getidlen(t_list *liste, int i)
{
	size_t		minsize;
	size_t		majsize;
	t_ls		*buf;
	t_list		*tmp;

	majsize = 0;
	tmp = ft_lstgetfirst(liste);
	minsize = 0;
	while (tmp != NULL)
	{
		buf = tmp->content;
		if (buf->strpermission[0] == 'c' || buf->strpermission[0] == 'b')
		{
			if (ft_strlen(buf->strmaj) > majsize)
				majsize = ft_strlen(buf->strmaj);
			if (ft_strlen(buf->strmin) > minsize)
				minsize = ft_strlen(buf->strmin);
		}
		tmp = tmp->next;
	}
	if (i == 0)
		return (majsize);
	else
		return (minsize);
}

void	ft_devmin(t_list *liste, size_t minlen)
{
	size_t		k;
	size_t		j;
	char		*tmp;
	t_ls		*buf;
	t_list		*list;

	list = ft_lstgetfirst(liste);
	while (list != NULL)
	{
		buf = list->content;
		if (buf->strpermission[0] == 'c' || buf->strpermission[0] == 'b')
		{
			if (ft_strlen(buf->strmin) < minlen)
			{
				k = 0;
				j = minlen - (ft_strlen(buf->strmin));
				tmp = getblank(j, k);
				buf->strmin = ft_strjoinfree(tmp, buf->strmin, 3);
			}
		}
		list = list->next;
	}
}

void	ft_devmaj(t_list *liste, size_t majlen)
{
	size_t		k;
	size_t		j;
	char		*tmp;
	t_ls		*buf;
	t_list		*list;

	list = ft_lstgetfirst(liste);
	while (list != NULL)
	{
		buf = list->content;
		if (buf->strpermission[0] == 'c' || buf->strpermission[0] == 'b')
		{
			if (ft_strlen(buf->strmaj) < majlen)
			{
				k = 0;
				j = majlen - (ft_strlen(buf->strmaj));
				tmp = getblank(j, k);
				buf->strmaj = ft_strjoinfree(tmp, buf->strmaj, 3);
			}
		}
		list = list->next;
	}
}

void	ft_cleanid(t_list *liste)
{
	int		i;
	size_t	majlen;
	size_t	minlen;
	t_ls	*buf;

	i = 0;
	majlen = ft_getidlen(liste, 0) + 3;
	minlen = ft_getidlen(liste, 1);
	ft_devmin(liste, minlen);
	ft_devmaj(liste, majlen);
	liste = ft_lstgetfirst(liste);
	while (liste != NULL)
	{
		buf = liste->content;
		buf->strmaj = ft_strjoinfree(buf->strmaj, ", ", 1);
		buf->strmaj = ft_strjoinfree(buf->strmaj, buf->strmin, 1);
		if (liste->next != NULL)
			liste = liste->next;
		else
			break ;
	}
	liste = ft_lstgetfirst(liste);
}
