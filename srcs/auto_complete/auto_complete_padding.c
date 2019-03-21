/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_padding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	give_id(void)
{
	int			i;
	int			a;
	t_list		*tmp;
	t_ls		*arg;

	tmp = ft_lstgetfirst(g_tracking.aut->comp_list->firstelement);
	i = lstcontainer_size(g_tracking.aut->comp_list);
	a = 0;
	while (tmp)
	{
		arg = tmp->content;
		arg->id = a;
		a++;
		tmp = tmp->next;
	}
	color(g_tracking.aut->comp_list->firstelement);
}

void	ft_strpadding(void)
{
	int			i;
	int			a;
	char		*blank;
	t_list		*tmp;
	t_ls		*arg;

	tmp = g_tracking.aut->comp_list->firstelement;
	while (tmp)
	{
		arg = tmp->content;
		a = ft_strlen(arg->name);
		a = g_tracking.aut->size - a;
		blank = ft_strnew(a + 1);
		i = 0;
		while (i <= a)
		{
			blank[i] = ' ';
			i++;
		}
		arg->strpad = blank;
		tmp = tmp->next;
	}
	give_id();
}

void	get_max_size(void)
{
	t_ls			*tmp;
	t_list			*buf;
	t_lstcontainer	*list;
	int				a;
	int				size;

	list = g_tracking.aut->comp_list;
	buf = ft_lstgetfirst(list->firstelement);
	size = 0;
	while (buf)
	{
		tmp = buf->content;
		a = ft_strlen(tmp->name);
		if (a > size)
			size = a;
		buf = buf->next;
	}
	g_tracking.aut->size = size;
	g_tracking.aut->col_nbr =
	g_tracking.terminfo->sizex / (g_tracking.aut->size + 6);
	g_tracking.aut->lin_nbr = g_tracking.terminfo->sizey - 2;
	if (g_tracking.aut->lin_nbr > 4)
		g_tracking.aut->lin_nbr = 4;
	ft_strpadding();
}

void	get_line_col(void)
{
	int				max;

	max = g_tracking.aut->size;
	g_tracking.aut->col_nbr = g_tracking.terminfo->sizex / (max);
	g_tracking.aut->lin_nbr = g_tracking.terminfo->sizey - 2;
}
