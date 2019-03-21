/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortoption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 21:22:08 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:21:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		whatsort(char *option)
{
	if (checkoption(option, 't') == 1)
		return (1);
	if (checkoption(option, 'S') == 1)
		return (2);
	return (0);
}

void	ft_sort(t_list *liste, char *option)
{
	int		flag;
	int		i;
	t_list	*buf;

	flag = whatsort(option);
	buf = ft_lstgetfirst(liste);
	if (flag == 0)
		ft_mergesort(buf, 0);
	if (flag == 1)
	{
		ft_mergesort(buf, 2);
		buf = ft_lstgetfirst(buf);
		ft_mergesort(buf, 3);
	}
	if (flag == 2)
		ft_mergesort(buf, 1);
	buf = ft_lstgetfirst(buf);
	i = 0;
	while (buf != NULL)
	{
		buf->index = i;
		i++;
		buf = buf->next;
	}
	liste = ft_lstgetfirst(liste);
}

void	reindex(t_list *liste)
{
	t_list	*buf;
	int		i;

	buf = ft_lstgetfirst(liste);
	i = 0;
	while (buf)
	{
		buf->index = i;
		i++;
		buf = buf->next;
	}
}
