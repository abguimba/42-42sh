/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 07:37:39 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
		list->firstelement = NULL;
		ft_free(list);
		list = NULL;
	}
}

void		clean_up_leaks(void)
{
	if (g_tracking.aut)
		clean_up_autoc();
	ft_strdel(&g_tracking.str);
	g_tracking.str = NULL;
	ft_free(g_tracking.terminfo);
	g_tracking.terminfo = NULL;
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = NULL;
	ft_strdel(&g_tracking.prompt);
	g_tracking.prompt = NULL;
	ft_strdel(&g_tracking.user);
	g_tracking.user = NULL;
	ft_strdel(&g_tracking.cwd);
	g_tracking.cwd = NULL;
}

int			ft_exit2(int exitcode)
{
	char	**hold;
	int		count;
	int		save;

	hold = g_tracking.g_tab_exec;
	count = 0;
	save = exitcode;
	if (hold)
		while (hold[count])
			count++;
	if (count > 2)
		return (exit_errors(0));
	else if (count == 2)
	{
		exitcode = ft_atoi(hold[1]);
		if ((exitcode < 0 || exitcode == save) && ft_strcmp(hold[1], "0"))
			return (ft_exit3(exit_errors(1), 2));
	}
	return (ft_exit3(exitcode, 2));
}
