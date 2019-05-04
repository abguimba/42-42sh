/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 00:18:46 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 07:29:44 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*truename(char *str)
{
	int i;
	int	chk;

	i = 0;
	chk = 0;
	while (str[i])
	{
		if (str[i] == '/')
			chk = i;
		i++;
	}
	return (&str[chk + 1]);
}

char	*truename2(char *str)
{
	int i;
	int	chk;

	i = 0;
	chk = 0;
	while (str[i])
	{
		if (str[i] == '/')
			chk = i;
		i++;
	}
	return (&str[chk]);
}

int		ft_cleanpath(char *str)
{
	char	*path;
	int		i;

	i = 0;
	path = truename(str);
	if (ft_strcmp(path, ".") != 0 && ft_strcmp(path, "..") != 0)
		return (0);
	else
		return (1);
}

void	makepath(char **path, char *str, char *name)
{
	if (ft_strcmp(str, "/") != 0)
		*path = ft_strjoinfree(str, "/", 0);
	else
		*path = ft_strdup(str);
	*path = ft_strjoinfree(*path, name, 1);
}

int		ft_edgecase(char *dossier)
{
	int		i;
	DIR		*dir;
	char	*err;

	i = ft_strlen(dossier) - 1;
	err = NULL;
	if (i < 0 || !dossier)
		return (1);
	if (dossier[i] == '/')
	{
		dir = opendir(dossier);
		if (!is_dir(dossier))
		{
			if (g_tracking.aut)
				g_tracking.aut->err = 1;
			return (1);
		}
		if (dir)
			closedir(dir);
	}
	return (0);
}
