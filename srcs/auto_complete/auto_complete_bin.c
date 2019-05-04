/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 03:01:52 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int					check_double(char *test)
{
	t_list			*buf;
	t_ls			*tmp;

	if (!test)
		return (1);
	if (g_tracking.aut->bin_lst)
	{
		buf = g_tracking.aut->bin_lst->firstelement;
		while (buf)
		{
			tmp = buf->content;
			if (tmp)
			{
				if (ft_strcmp(tmp->name, test) == 0)
					return (1);
			}
			buf = buf->next;
		}
	}
	return (0);
}

void				builtin_lst(void)
{
	char			*tmp;
	t_list			*buf;
	t_ls			*new;

	tmp = NULL;
	if (g_tracking.builtin_list)
	{
		buf = g_tracking.builtin_list->firstelement;
		while (buf)
		{
			tmp = buf->content;
			if (tmp && check_double(tmp) == 0)
			{
				new = ls_alloc(tmp);
				lstcontainer_add(g_tracking.aut->bin_lst, new);
			}
			buf = buf->next;
		}
	}
}

t_lstcontainer		*bin_ls(char *str)
{
	t_lstcontainer	*liste;
	char			**taab;

	taab = ft_malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = str;
	liste = modified_ls(2, taab);
	ft_free(taab);
	return (liste);
}

void				bin_lst_folder(char *str)
{
	t_lstcontainer	*local_lst;
	t_list			*buf;
	t_ls			*tmp;
	t_ls			*new;

	local_lst = NULL;
	buf = NULL;
	tmp = NULL;
	local_lst = bin_ls(str);
	if (local_lst)
	{
		buf = local_lst->firstelement;
		while (buf)
		{
			tmp = buf->content;
			new = ls_alloc(tmp->name);
			lstcontainer_add(g_tracking.aut->bin_lst, new);
			buf = buf->next;
		}
	}
	free_all(local_lst, NULL);
}

void				build_bin_lst(void)
{
	char			*path;
	char			**split;
	int				i;

	path = NULL;
	split = NULL;
	i = 0;
	path = get_env_string("PATH");
	g_tracking.aut->bin_lst = lstcontainer_new();
	if (!path)
		return ;
	split = ft_strsplit(path, ':');
	if (!split)
		return ;
	while (split[i])
	{
		bin_lst_folder(split[i]);
		i++;
	}
	free_tab(split);
	builtin_lst();
}
