/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_auto	*init_auto(void)
{
	t_auto		*aut;

	if (!(aut = ft_malloc(sizeof(t_auto))))
		return (NULL);
	aut->word = NULL;
	aut->path = NULL;
	aut->menuline = NULL;
	aut->comp_list = NULL;
	aut->var_lst = NULL;
	aut->bin_lst = NULL;
	aut->to_free = NULL;
	aut->to_add = NULL;
	aut->page_lst = NULL;
	aut->size = 0;
	aut->col_nbr = 0;
	aut->lin_nbr = 0;
	aut->line_up = 0;
	aut->type = 0;
	aut->hidden = 0;
	aut->err = 0;
	aut->to_add_y = 0;
	aut->to_rem = 0;
	return (aut);
}

void	build_list(void)
{
	g_tracking.aut->comp_list = NULL;
	if (g_tracking.aut->word)
		complete_usr_word();
	else
	{
		g_tracking.aut->comp_list = build_ls();
		if (!g_tracking.aut->comp_list)
			return ;
		get_max_size();
		set_up_page();
		completion_loop(g_tracking.aut->comp_list);
	}
}

int		auto_complete(void)
{
	if ((g_tracking.aut = init_auto()) == NULL)
		return (1);
	build_bin_lst();
	build_var_lst();
	assign_word();
	build_list();
	clean_up_autoc();
	return (0);
}
