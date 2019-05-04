/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:36:15 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 01:02:41 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			test_exist_dir(char *path)
{
	DIR		*dir;

	dir = opendir(path);
	if (!dir)
		return (-1);
	closedir(dir);
	return (0);
}

char		*add_slash(char *pathname)
{
	int		i;

	if (!pathname)
		return (pathname);
	i = ft_strlen(pathname);
	if (pathname[i] != '/')
		pathname = ft_strjoinchar(pathname, '/', 1);
	return (pathname);
}

char		*conc_test(t_list *tmp, char *path)
{
	char	*test;

	if (!tmp || !path)
		return (path);
	while (tmp)
	{
		test = ft_strdup(tmp->content);
		test = add_slash(test);
		test = ft_strjoinfree(test, path, 1);
		if (test_exist_dir(test) == 0)
		{
			ft_strdel(&path);
			return (test);
		}
		tmp = tmp->next;
	}
	ft_strdel(&test);
	test = ft_strdup(get_env_string("PWD"));
	if (!test)
		test = ft_true_pwd();
	test = add_slash(test);
	test = ft_strjoinfree(test, path, 3);
	return (test);
}

char		*cd_path(char *path)
{
	t_lstcontainer		*list;
	t_list				*tmp;
	char				*cdpath;

	if (!g_tracking.mysh->env)
		return (path);
	cdpath = ft_strdup(get_set_env_string("CDPATH"));
	if (!cdpath)
		return (path);
	list = ft_strsplitlst(cdpath, ';');
	ft_free(cdpath);
	if (!list)
		return (path);
	tmp = list->firstelement;
	path = conc_test(tmp, path);
	ft_freesplitlist(list);
	return (path);
}
