/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lstcontainer		*bin_ls(char *str)
{
	t_lstcontainer	*liste;
	char			**taab;

	taab = malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = str;
	liste = modified_ls(2, taab);
	free(taab);
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
}

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
			free(g_tracking.aut->comp_list);
			build_comp(g_tracking.aut->bin_lst);
		}
		g_tracking.aut->to_add = NULL;
		if (g_tracking.aut->comp_list->firstelement != NULL)
		{
			get_max_size();
			rem_str(g_tracking.aut->word);
			set_up_page();
			completion_loop(g_tracking.aut->comp_list);
		}
	}
}
