/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 10:56:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				complete_usr_var(void)
{
	t_lstcontainer	*list;

	list = NULL;
	list = g_tracking.aut->var_lst;
	if (list != NULL)
	{
		build_comp(list);
		g_tracking.aut->to_add = NULL;
		if (g_tracking.aut->comp_list->firstelement != NULL)
		{
			get_max_size();
			end_word(1);
			rem_str(g_tracking.aut->word);
			set_up_page();
			completion_loop(g_tracking.aut->comp_list);
		}
	}
}

void				complete_usr_word(void)
{
	t_lstcontainer	*list;

	list = NULL;
	assign_type();
	list = build_ls();
	g_tracking.aut->to_free = list;
	if (list != NULL && g_tracking.aut->type != 2)
	{
		build_comp(list);
		if (g_tracking.aut->comp_list->firstelement == NULL)
		{
			ft_free(g_tracking.aut->comp_list);
			build_comp(g_tracking.aut->bin_lst);
		}
		g_tracking.aut->to_add = NULL;
		if (g_tracking.aut->comp_list->firstelement != NULL)
		{
			get_max_size();
			end_word(1);
			rem_str(g_tracking.aut->word);
			set_up_page();
			completion_loop(g_tracking.aut->comp_list);
		}
	}
}
