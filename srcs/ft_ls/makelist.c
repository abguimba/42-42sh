/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:42:49 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 07:27:55 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

DIR				*chkdir(char *str, int *check)
{
	DIR		*dir;

	dir = opendir(str);
	*check = 0;
	if (dir == NULL)
	{
		if (!is_dir(str))
			*check = 1;
		else
			ft_free(dir);
		return (NULL);
	}
	else
		return (dir);
}

t_lstcontainer	*simpleinfo(char *str, char *option)
{
	t_ls				*info;
	t_lstcontainer		*mainliste;

	mainliste = lstcontainer_new();
	info = str_alloc();
	info->name = ft_strdup(str);
	if (ft_stat(str, info, option) == 0)
	{
		if (ft_strncmp(str, "./", 2) != 0)
			info->path = ft_strjoinfree("./", str, 0);
		else
			info->path = ft_strdup(str);
		lstcontainer_add(mainliste, info);
	}
	else
		ft_freestructlite(info);
	return (mainliste);
}

void			addstruct(t_lstcontainer *mainliste, char *option,
				t_ls *info, int a)
{
	if (needstat(option) == 1)
	{
		if (ft_stat(info->path, info, option) == 0)
		{
			if (info->name[0] == '.' && a == 1)
				lstcontainer_add(mainliste, info);
			if (info->name[0] != '.')
				lstcontainer_add(mainliste, info);
			if (info->name[0] == '.' && a == 0)
				ft_freestructlite(info);
		}
		else
			ft_freestructlite(info);
	}
	else
	{
		if (info->name[0] == '.' && a == 1)
			lstcontainer_add(mainliste, info);
		if (info->name[0] != '.')
			lstcontainer_add(mainliste, info);
		if (info->name[0] == '.' && a == 0)
			ft_freestructlite(info);
	}
}

t_lstcontainer	*makelist(t_lstcontainer *mainliste, DIR *dir,
				char *str, char *option)
{
	t_ls			*info;
	struct dirent	*file;
	char			*path;
	int				a;

	a = checkoption(option, 'a');
	while ((file = readdir(dir)) != NULL)
	{
		info = str_alloc();
		makepath(&path, str, file->d_name);
		info->path = path;
		info->name = ft_strdup(file->d_name);
		info->issimple = 0;
		addstruct(mainliste, option, info, a);
	}
	ft_free(file);
	return (mainliste);
}
