/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanusr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 00:36:57 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_getmaxusr(t_list *liste)
{
	size_t		maxusr;
	t_ls		*buf;

	maxusr = 0;
	liste = ft_lstgetfirst(liste);
	while (liste != NULL)
	{
		buf = liste->content;
		if (ft_strlen(buf->strusrname) > maxusr)
			maxusr = ft_strlen(buf->strusrname);
		if (liste->next != NULL)
			liste = liste->next;
		else
			break ;
	}
	return (maxusr);
}

void	ft_spaceusr(t_list *liste)
{
	t_ls		*tmp;
	size_t		j;
	size_t		k;
	size_t		max;
	char		*buf;

	liste = ft_lstgetfirst(liste);
	max = ft_getmaxusr(liste) + 1;
	while (liste != NULL)
	{
		tmp = liste->content;
		if (ft_strlen(tmp->strusrname) < max && ft_strlen(tmp->strusrname) != 0)
		{
			k = 0;
			j = max - (ft_strlen(tmp->strusrname));
			buf = getblank(j, k);
			tmp->strusrname = ft_strjoinfree(tmp->strusrname, buf, 3);
		}
		if (liste->next != NULL)
			liste = liste->next;
		else
			break ;
	}
}
