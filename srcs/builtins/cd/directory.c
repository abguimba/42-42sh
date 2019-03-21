/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:29:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/05 04:07:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*getname(char *path)
{
	char	*name;
	char	**taab;
	int		i;

	i = 0;
	name = NULL;
	if ((taab = ft_strsplit(path, '/')) != NULL)
	{
		while (taab[i])
		{
			i++;
		}
		if (i != 0)
		{
			name = ft_strdup(taab[i - 1]);
		}
		free_tab(taab);
		free(path);
		return (name);
	}
	else
		return (NULL);
}

void	free_stuff(char *name, char *path)
{
	free(name);
	name = NULL;
	free(path);
	path = NULL;
}

int		getright2(char *path, char *name)
{
	if (ft_isdir(path) == 0)
	{
		ft_putstr("Not a directory: ");
		ft_putendl(path);
		free_stuff(name, path);
		return (1);
	}
	if (access(path, R_OK) != 0)
	{
		ft_putstr("Permission denied: ");
		ft_putendl(path);
		free_stuff(name, path);
		return (1);
	}
	free_stuff(name, path);
	return (0);
}

int		getright(char *str)
{
	char *name;
	char *path;

	path = ft_strdup(str);
	name = ft_strdup(path);
	if (ft_strcmp(str, "/") != 0)
		name = getname(name);
	if (name == NULL)
		return (2);
	if (access(path, F_OK) != 0)
	{
		ft_putstr("No such file or directory: ");
		ft_putendl(path);
		free_stuff(name, path);
		return (1);
	}
	return (getright2(path, name));
}
