/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		free_and_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void		free_keyval(t_lstcontainer *list)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (list)
	{
		tmp = ft_lstgetfirst(list->firstelement);
		while (tmp)
		{
			buf = tmp->content;
			if (buf)
			{
				free_and_null(buf->key);
				free_and_null(buf->value);
			}
			tmp = tmp->next;
		}
		ft_lstdel(list->firstelement, 1);
		free(list);
		list = NULL;
	}
}

void		clean_up_leaks(void)
{
	if (g_tracking.aut)
		clean_up_autoc();
	if (g_tracking.mysh->alias_lst)
	{
		free_keyval(g_tracking.mysh->alias_lst);
		g_tracking.mysh->alias_lst = NULL;
	}
	if (g_tracking.mysh->hist)
		ctrl_c();
	free(g_tracking.str);
	free(g_tracking.cpaste->line);
	g_tracking.str = NULL;
}

int			ft_exit(void)
{
	t_jobs	*tmp;

	tmp = g_tracking.jobs;
	while (tmp && tmp->next)
	{
		if (tmp->background == 1)
		{
			ft_putendl("There are still background jobs running!");
			return (1);
		}
		tmp = tmp->next;
	}
	hist_save_file(g_tracking.mysh->hist);
	free_hist();
	clean_up_leaks();
	clean_up_leaks();
	exit(0);
}
