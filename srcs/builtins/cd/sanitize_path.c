/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:27:48 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 02:14:09 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*add_pwd(char *path, char option)
{
	char		*pwd;

	if (option == 'P')
		pwd = ft_true_pwd();
	else
		pwd = ft_strdup(get_env_string("PWD"));
	if (!pwd)
		pwd = ft_true_pwd();
	pwd = add_slash(pwd);
	pwd = ft_strjoinfree(pwd, path, 3);
	return (pwd);
}

void		remove_dotdot(t_lstcontainer *list)
{
	t_list	*tmp;

	tmp = ft_lstgetfirst(list->firstelement);
	while (tmp)
	{
		if (ft_strcmp("..", tmp->content) == 0)
		{
			if (tmp->prev)
				list->remove(list, tmp->prev, 1);
			list->remove(list, tmp, 1);
			tmp = ft_lstgetfirst(list->firstelement);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void		remove_dot(t_lstcontainer *list)
{
	t_list	*tmp;

	tmp = ft_lstgetfirst(list->firstelement);
	while (tmp)
	{
		if (ft_strcmp(".", tmp->content) == 0)
		{
			list->remove(list, tmp, 1);
			tmp = ft_lstgetfirst(list->firstelement);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

char		*path_from_list(t_list *tmp)
{
	char	*newpath;
	char	*addon;

	newpath = NULL;
	if (!tmp)
		newpath = ft_strdup("/");
	while (tmp)
	{
		addon = ft_strjoinfree("/", tmp->content, 0);
		newpath = ft_strjoinfree(newpath, addon, 3);
		tmp = tmp->next;
	}
	return (newpath);
}

char		*sanitize_path_cd(char *path, char option)
{
	t_lstcontainer	*list;
	t_list			*tmp;

	list = NULL;
	if (!path)
		return (NULL);
	if (path[0] != '/')
		path = add_pwd(path, option);
	list = ft_strsplitlst(path, '/');
	if (list)
	{
		tmp = list->firstelement;
		ft_free(path);
		remove_dotdot(list);
		remove_dotdot(list);
		remove_dot(list);
		path = path_from_list(list->firstelement);
		ft_freesplitlist(list);
	}
	path = check_multi_slash(path);
	return (path);
}
