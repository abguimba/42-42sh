/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/28 05:02:41 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				free_contents(t_list *buf)
{
	t_keyval		*tmp;

	while (buf)
	{
		tmp = buf->content;
		ft_strdel(&tmp->key);
		ft_strdel(&tmp->value);
		buf = buf->next;
	}
}

int					unalias_blt(void)
{
	char			**av;
	t_list			*buf;

	if (!g_tracking.mysh->alias_lst)
		return (1);
	av = g_tracking.g_tab_exec;
	if (!av[1])
	{
		ft_putendl_fd("unalias [-a] [name … ]", 2);
		return (1);
	}
	if (ft_strcmp(av[1], "-a") == 0)
	{
		if (g_tracking.mysh->alias_lst)
		{
			buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
			free_contents(buf);
		}
		ft_lstdel(g_tracking.mysh->alias_lst->firstelement, 1);
		ft_free(g_tracking.mysh->alias_lst);
		g_tracking.mysh->alias_lst = lstcontainer_new();
	}
	else
		unalias(av[1]);
	return (0);
}

int					unalias(char *alias)
{
	t_keyval		*tmp;
	t_list			*buf;

	if (!g_tracking.mysh->alias_lst || !alias)
		return (1);
	buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (ft_strcmp(tmp->key, alias) == 0)
			{
				ft_strdel(&tmp->key);
				ft_strdel(&tmp->value);
				lstcontainer_remove(g_tracking.mysh->alias_lst, buf, 1);
				return (1);
			}
		}
		buf = buf->next;
	}
	return (0);
}
