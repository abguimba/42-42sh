/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 00:36:57 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:41:14 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_cleantime(t_list *liste)
{
	char		*tmp;
	char		*dup;
	t_ls		*buf;
	t_list		*list;

	list = ft_lstgetfirst(liste);
	while (list != NULL)
	{
		buf = list->content;
		dup = ft_strdup(buf->strtime);
		free(buf->strtime);
		if (buf->timeswitch == 1)
		{
			tmp = ft_subtime(dup, tmp);
			buf->strtime = tmp;
		}
		else
		{
			tmp = ft_strsub(dup, 4, 12, 1);
			buf->strtime = tmp;
		}
		list = list->next;
	}
}

int		ft_getmaxlen(t_list *liste, int i, size_t maxsize)
{
	size_t		maxlink;
	size_t		maxgroup;
	t_ls		*buf;
	t_list		*tmp;

	maxlink = 0;
	maxgroup = 0;
	tmp = ft_lstgetfirst(liste);
	while (tmp != NULL)
	{
		buf = tmp->content;
		if (ft_strlen(buf->strlink) > maxlink)
			maxlink = ft_strlen(buf->strlink);
		if (ft_strlen(buf->strsize) > maxsize)
			maxsize = ft_strlen(buf->strsize);
		if (ft_strlen(buf->strgroup) > maxgroup)
			maxgroup = ft_strlen(buf->strgroup);
		tmp = tmp->next;
	}
	if (i == 0)
		return (maxlink);
	if (i == 1)
		return (maxsize);
	else
		return (maxgroup);
}

void	ft_spacelink(t_list *liste)
{
	t_ls		*tmp;
	size_t		j;
	size_t		k;
	size_t		max;
	char		*buf;

	liste = ft_lstgetfirst(liste);
	max = ft_getmaxlen(liste, 0, 0);
	while (liste != NULL)
	{
		tmp = liste->content;
		if (ft_strlen(tmp->strlink) < max)
		{
			k = 0;
			j = max - (ft_strlen(tmp->strlink));
			buf = getblank(j, k);
			tmp->strlink = ft_strjoinfree(buf, tmp->strlink, 3);
		}
		if (liste->next != NULL)
			liste = liste->next;
		else
			break ;
	}
}

void	ft_spacesize(t_list *liste)
{
	t_ls		*tmp;
	size_t		j;
	size_t		k;
	size_t		max;
	char		*buf;

	liste = ft_lstgetfirst(liste);
	max = getspacesize(liste) + 1;
	if (ft_getidlen(liste, 0) != 0)
		max = max - 2;
	while (liste != NULL)
	{
		tmp = liste->content;
		if (ft_strlen(tmp->strsize) < max && ft_strlen(tmp->strsize) != 0)
		{
			k = 0;
			j = max - (ft_strlen(tmp->strsize));
			buf = getblank(j, k);
			tmp->strsize = ft_strjoinfree(buf, tmp->strsize, 3);
		}
		if (liste->next != NULL)
			liste = liste->next;
		else
			break ;
	}
}

void	ft_spacegroup(t_list *liste)
{
	t_ls		*tmp;
	size_t		j;
	size_t		k;
	size_t		max;
	char		*buf;

	liste = ft_lstgetfirst(liste);
	max = ft_getmaxlen(liste, 2, 0);
	while (liste != NULL)
	{
		tmp = liste->content;
		if (ft_strlen(tmp->strgroup) < max && ft_strlen(tmp->strgroup) != 0)
		{
			k = 0;
			j = max - (ft_strlen(tmp->strgroup));
			buf = getblank(j, k);
			tmp->strgroup = ft_strjoinfree(tmp->strgroup, buf, 3);
		}
		if (liste->next != NULL)
			liste = liste->next;
		else
			break ;
	}
}
