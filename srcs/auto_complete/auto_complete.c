/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 03:00:07 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		loop_for_space(int i)
{
	while (g_tracking.str[i] != ' ' && i != 0)
		i--;
	return (i);
}

void	asign_word(int i, unsigned long a, int flag)
{
	if (ft_strlen(g_tracking.str) != 0)
	{
		flag = 0;
		i = utf_goto(g_tracking.str, g_tracking.pos->abs);
		a = i;
		while (flag == 0 && i != 0)
		{
			i = loop_for_space(i);
			if (i != 0)
			{
				if (g_tracking.str[i - 1] != '\\')
					flag = 1;
				else
					i--;
			}
		}
		if (g_tracking.str[i] == ' ')
			i++;
		while (g_tracking.str[a] != ' ' && a != ft_strlen(g_tracking.str))
			a++;
		a = a - i;
		if (a != 0)
			g_tracking.aut->word = ft_strsub(g_tracking.str, i, a, 0);
	}
}

t_auto	*init_auto(void)
{
	t_auto		*aut;

	if (!(aut = malloc(sizeof(t_auto))))
		return (NULL);
	aut->word = NULL;
	aut->path = NULL;
	aut->menuline = NULL;
	aut->comp_list = NULL;
	aut->var_lst = NULL;
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
	asign_word(0, 0, 0);
	build_list();
	clean_up_autoc();
	return (0);
}
