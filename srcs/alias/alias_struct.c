/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:29:58 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 03:07:31 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lstcontainer		*alias_error(char *alias)
{
	t_lstcontainer	*split;

	if (!alias)
		return (NULL);
	split = ft_strsplitlst(alias, '=');
	if (lstcontainer_size(split) < 2)
	{
		ft_putstr("Wrong alias : ");
		ft_putendl(alias);
		ft_putendl("Usage: Alias [alias]=[cmd]");
		ft_freesplitlist(split);
		return (NULL);
	}
	unalias(split->firstelement->content);
	return (split);
}

t_keyval			*parse_alias(char *alias)
{
	t_lstcontainer	*split;
	t_keyval		*al_to_add;
	t_list			*tmp;

	al_to_add = NULL;
	split = alias_error(alias);
	if (!(al_to_add = malloc(sizeof(struct s_keyval))) || split == NULL)
		return (NULL);
	tmp = split->firstelement;
	al_to_add->key = ft_strdup(tmp->content);
	tmp = tmp->next;
	al_to_add->value = NULL;
	while (tmp)
	{
		if (!al_to_add->value)
			al_to_add->value = ft_strnew(0);
		al_to_add->value = ft_strjoinfree(al_to_add->value, tmp->content, 1);
		tmp = tmp->next;
	}
	ft_freesplitlist(split);
	return (al_to_add);
}

int					add_alias(void)
{
	t_lstcontainer	*alias_lst;
	t_keyval		*alias_to_add;
	char			**av;
	char			*alias;

	av = g_tracking.g_tab_exec;
	if (!av[1])
	{
		print_alias_lst();
		return (0);
	}
	alias = ft_strdup(av[1]);
	alias_lst = g_tracking.mysh->alias_lst;
	alias_to_add = parse_alias(alias);
	if (alias_lst && alias_to_add)
		lstcontainer_add(alias_lst, parse_alias(alias));
	return (0);
}

int					unalias_blt(void)
{
	char			**av;

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
		ft_lstdel(g_tracking.mysh->alias_lst->firstelement, 1);
		free(g_tracking.mysh->alias_lst);
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
				lstcontainer_remove(g_tracking.mysh->alias_lst, buf, 1);
				return (1);
			}
		}
		buf = buf->next;
	}
	return (0);
}
