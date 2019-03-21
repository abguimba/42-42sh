/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 19:23:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/05 04:12:32 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_homepath(char *path)
{
	int		i;
	char	*new;
	char	*home;

	i = 0;
	if (!path)
		return (NULL);
	new = ft_strdup(path);
	free(path);
	if (new[i] == '~' && (new[i + 1] == '\0' || new[i + 1] == '/'))
	{
		new = ft_strsub(new, 1, ft_strlen(new), 1);
		home = get_env_string("HOME");
		path = ft_strjoinfree(home, new, 2);
		new = NULL;
	}
	else
		path = new;
	return (path);
}

int		ft_handlestat(struct stat *tmp, char *permission, char *path)
{
	if (permission == NULL)
		return (1);
	if (permission[0] != 'd' && permission[0] != 'l')
		return (0);
	else
	{
		if (permission[0] == 'l')
		{
			stat(path, tmp);
			permission = ft_usrmode(tmp->st_mode);
			if (permission[0] != 'd')
				return (0);
		}
	}
	return (1);
}

int		ft_isdir(char *path)
{
	struct stat		*tmp;
	char			*permission;
	int				i;

	tmp = malloc(sizeof(struct stat));
	if (path)
	{
		if (lstat(path, tmp) != -1)
		{
			permission = ft_usrmode(tmp->st_mode);
			i = ft_handlestat(tmp, permission, path);
			free(tmp);
			free(permission);
			return (i);
		}
		return (0);
	}
	return (0);
}
