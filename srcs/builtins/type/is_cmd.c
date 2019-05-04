/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 00:21:24 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 04:07:09 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*exist_fonction_two(char *cmd, char **pathlist)
{
	int		i;
	char	*next_str;

	i = 0;
	next_str = NULL;
	if (!pathlist)
		return (NULL);
	while (pathlist[i])
	{
		next_str = ft_strjoin(pathlist[i], "/");
		next_str = ft_strjoinfree(next_str, cmd, 1);
		if (access(next_str, X_OK) == 0)
			return (next_str);
		i++;
		ft_free(next_str);
	}
	return (NULL);
}

char	*exist_fonction(char *cmd)
{
	char		**pathlist;
	char		*path;

	if (!ft_strcmp(cmd, ".."))
		return (0);
	if (!ft_strcmp(cmd, "."))
		return (0);
	path = get_env_string("PATH");
	pathlist = ft_strsplit(path, ':');
	path = exist_fonction_two(cmd, pathlist);
	free_tab(pathlist);
	return (path);
}
