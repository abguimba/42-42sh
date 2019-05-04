/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:58:17 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_total(t_list *liste)
{
	t_ls	*tmp;
	t_list	*buf;
	long	i;

	i = 0;
	buf = ft_lstgetfirst(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		i += tmp->block;
		buf = buf->next;
	}
	ft_putstr("total ");
	ft_putnbr(i);
	ft_putchar('\n');
}

void	cleanup(t_list *liste)
{
	ft_cleantime(liste);
	ft_cleanid(liste);
	ft_spacegroup(liste);
	ft_spaceusr(liste);
	ft_spacesize(liste);
	ft_spacelink(liste);
}

int		ft_strinfo(t_list *liste)
{
	t_ls	*tmp;
	t_list	*buf;

	if (liste == NULL)
		return (0);
	buf = ft_lstgetfirst(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		tmp->strpermission = ft_usrmode(tmp->permission);
		tmp->strlink = NULL;
		tmp->strusrname = NULL;
		tmp->strgroup = NULL;
		tmp->strsize = NULL;
		tmp->strtime = NULL;
		tmp->strmin = NULL;
		tmp->strmaj = NULL;
		tmp->strpermission[10] = '\0';
		buf = buf->next;
	}
	liste = ft_lstgetfirst(liste);
	cleanup(liste);
	return (0);
}
