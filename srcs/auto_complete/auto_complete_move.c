/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_list	*skip_col(t_list *buf, int i)
{
	int			col;
	int			place;
	int			last;
	t_list		*end;

	col = g_tracking.aut->col_nbr;
	place = buf->index;
	end = ft_lstgetlast(buf);
	last = end->index;
	if (i == -2)
	{
		if (place - col >= 0)
			buf = ft_lstget(place - col, buf);
		else
			buf = ft_lstgetfirst(buf);
	}
	if (i == 2)
	{
		if (place + col <= last)
			buf = ft_lstget(place + col, buf);
		else
			buf = ft_lstgetlast(buf);
	}
	return (buf);
}

t_list	*move_arround(t_list *buf, int i)
{
	if (i == -1)
	{
		if (buf->prev == NULL)
			buf = ft_lstgetlast(buf);
		else
			buf = buf->prev;
	}
	if (i == 1)
	{
		if (buf->next == NULL)
			buf = ft_lstgetfirst(buf);
		else
			buf = buf->next;
	}
	if (i == 2 || i == -2)
		buf = skip_col(buf, i);
	return (buf);
}
