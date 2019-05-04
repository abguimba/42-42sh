/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:29:58 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 05:21:31 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int					check_forbidden_char(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '-' || str[i] == '/'
		|| str[i] == '~')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		ft_putstr_fd("forbidden char in alias : ", 2);
		ft_putendl_fd(str, 2);
	}
	return (flag);
}

int					print_alias(char *name)
{
	t_keyval		*tmp;
	t_list			*buf;

	if (!g_tracking.mysh->alias_lst || !name)
		return (alias_print_error(name));
	buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (ft_strcmp(tmp->key, name) == 0)
			{
				print_keyval(tmp);
				return (0);
			}
		}
		buf = buf->next;
	}
	return (alias_print_error(name));
}

t_lstcontainer		*alias_error(char *alias)
{
	t_lstcontainer	*split;
	t_list			*tmp;
	char			*alias_test;

	if (!alias)
		return (NULL);
	split = ft_strsplitlst(alias, '=');
	if (lstcontainer_size(split) > 2)
	{
		alias_add_error(alias);
		return (NULL);
	}
	tmp = split->firstelement;
	alias_test = tmp->content;
	if ((check_forbidden_char(alias_test) != 0))
	{
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
	if (!split || !(al_to_add = ft_malloc(sizeof(struct s_keyval))))
		return (NULL);
	tmp = split->firstelement;
	al_to_add->key = ft_strdup(tmp->content);
	tmp = tmp->next;
	al_to_add->value = NULL;
	al_to_add->loop = 0;
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

int					add_alias(int count, char **av)
{
	t_lstcontainer	*alias_lst;
	t_keyval		*alias_to_add;
	char			*alias;
	int				i;

	if (!av[1])
		return (print_alias_lst());
	i = 0;
	while (av[i++])
	{
		alias = ft_strdup(av[i]);
		alias_lst = g_tracking.mysh->alias_lst;
		count = search_eq(alias);
		if (count == 0)
			print_alias(alias);
		else if (count == 1)
		{
			alias_to_add = parse_alias(alias);
			if (alias_lst && alias_to_add)
				lstcontainer_add(alias_lst, alias_to_add);
		}
		ft_strdel(&alias);
	}
	return (0);
}
