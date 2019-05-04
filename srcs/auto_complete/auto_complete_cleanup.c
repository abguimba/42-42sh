/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 06:52:13 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	clean_up_pages(void)
{
	if (g_tracking.aut->page_lst)
	{
		ft_lstdel(g_tracking.aut->page_lst->firstelement, 0);
		ft_free(g_tracking.aut->page_lst);
	}
}

void	clean_up_tofree(void)
{
	free_all(g_tracking.aut->to_free, NULL);
	g_tracking.aut->to_free = NULL;
	ft_lstdel(g_tracking.aut->comp_list->firstelement, 0);
	ft_free(g_tracking.aut->comp_list);
}

void	clean_up_autoc(void)
{
	ft_strdel(&g_tracking.aut->word);
	ft_strdel(&g_tracking.aut->menuline);
	ft_strdel(&g_tracking.aut->path);
	if (g_tracking.aut->to_free)
		clean_up_tofree();
	else
	{
		free_all(g_tracking.aut->comp_list, NULL);
		g_tracking.aut->comp_list = NULL;
	}
	if (g_tracking.aut->var_lst)
	{
		free_all(g_tracking.aut->var_lst, NULL);
		g_tracking.aut->var_lst = NULL;
	}
	if (g_tracking.aut->bin_lst)
	{
		free_all(g_tracking.aut->bin_lst, NULL);
		g_tracking.aut->bin_lst = NULL;
	}
	ft_free(g_tracking.aut->to_add);
	clean_up_pages();
	ft_free(g_tracking.aut);
	g_tracking.aut = NULL;
}
