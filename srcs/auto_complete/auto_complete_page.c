/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_page.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 04:46:37 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				line_per_page(void)
{
	int				nb;
	int				rest;
	int				lin;

	nb = lstcontainer_size(g_tracking.aut->comp_list);
	rest = nb - (g_tracking.aut->per_page * (g_tracking.aut->page_nbr));
	g_tracking.aut->line_up = (nb + g_tracking.aut->col_nbr - 1)
	/ g_tracking.aut->col_nbr;
	if (g_tracking.aut->line_up > g_tracking.aut->lin_nbr)
		g_tracking.aut->line_up = g_tracking.aut->lin_nbr;
	lin = (rest + g_tracking.aut->col_nbr - 1) / g_tracking.aut->col_nbr;
	lin = g_tracking.aut->line_up - lin;
	g_tracking.aut->pad_lpage = lin;
}

void				set_up_page(void)
{
	int				nb;
	int				page;

	if (g_tracking.aut->lin_nbr < 1)
	{
		g_tracking.aut->err = 2;
		return ;
	}
	nb = lstcontainer_size(g_tracking.aut->comp_list) - 1;
	page = g_tracking.aut->lin_nbr * g_tracking.aut->col_nbr;
	if (page < 1)
	{
		g_tracking.aut->err = 2;
		return ;
	}
	g_tracking.aut->per_page = page;
	g_tracking.aut->page_nbr = nb / page;
	g_tracking.aut->active_page = 0;
}

void				change_page(int i, t_lstcontainer *list)
{
	ft_lstdel(g_tracking.aut->page_lst->firstelement, 0);
	ft_free(g_tracking.aut->page_lst);
	g_tracking.aut->page_lst = NULL;
	g_tracking.aut->last_page = g_tracking.aut->active_page;
	if (i == 3)
	{
		if (g_tracking.aut->active_page < g_tracking.aut->page_nbr)
			g_tracking.aut->active_page++;
	}
	if (i == -3)
	{
		if (g_tracking.aut->active_page > 0)
			g_tracking.aut->active_page--;
	}
	g_tracking.aut->page_lst = build_page_lst(list);
}

t_lstcontainer		*build_page_lst(t_lstcontainer *list)
{
	t_lstcontainer	*page_lst;
	t_list			*buf;
	t_ls			*tmp;
	int				begin;
	int				end;

	begin = g_tracking.aut->active_page * g_tracking.aut->per_page;
	end = g_tracking.aut->per_page * (g_tracking.aut->active_page + 1);
	page_lst = lstcontainer_new();
	buf = ft_lstget(begin, list->firstelement);
	while (buf && begin < end)
	{
		tmp = buf->content;
		lstcontainer_add(page_lst, tmp);
		begin++;
		buf = buf->next;
	}
	return (page_lst);
}

void				join_page_nbr(void)
{
	char			*page_nbr;
	char			*total_page;
	char			*message;
	int				i;
	int				j;

	if (g_tracking.aut->active_page == g_tracking.aut->page_nbr)
	{
		i = 0;
		j = g_tracking.aut->pad_lpage;
		while (j > i)
		{
			ft_putstr("\n");
			i++;
		}
	}
	page_nbr = ft_itoa(g_tracking.aut->active_page + 1);
	total_page = ft_itoa(g_tracking.aut->page_nbr + 1);
	message = ft_strdup("page ");
	message = ft_strjoinfree(message, page_nbr, 3);
	message = ft_strjoinfree(message, "/", 1);
	message = ft_strjoinfree(message, total_page, 3);
	ft_putstr(message);
	ft_free(message);
}
