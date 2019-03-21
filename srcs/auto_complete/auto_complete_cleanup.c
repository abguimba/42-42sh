/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 06:52:13 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	clean_up_pages(void)
{
	if (g_tracking.aut->page_lst)
	{
		ft_lstdel(g_tracking.aut->page_lst->firstelement, 0);
		free(g_tracking.aut->page_lst);
	}
}

void	clean_up_tofree(void)
{
	free_all(g_tracking.aut->to_free, NULL);
	g_tracking.aut->to_free = NULL;
	ft_lstdel(g_tracking.aut->comp_list->firstelement, 0);
	free(g_tracking.aut->comp_list);
}

void	clean_up_autoc(void)
{
	free(g_tracking.aut->word);
	g_tracking.aut->word = NULL;
	free(g_tracking.aut->menuline);
	g_tracking.aut->menuline = NULL;
	free(g_tracking.aut->path);
	g_tracking.aut->path = NULL;
	if (g_tracking.aut->to_free)
		clean_up_tofree();
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
	free(g_tracking.aut->to_add);
	clean_up_pages();
	free(g_tracking.aut);
	g_tracking.aut = NULL;
}
