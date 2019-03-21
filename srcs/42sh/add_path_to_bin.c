/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:00:43 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/15 19:29:59 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

int		test_exist_fonction_two(char ***tab_cmd, char **pathlist)
{
	int		i;
	char	*next_str;
	char	*addslash;

	i = 0;
	next_str = NULL;
	if (!pathlist)
		return (0);
	while (pathlist[i])
	{
		addslash = ft_strjoin(pathlist[i], "/");
		next_str = ft_strjoin(addslash, *tab_cmd[0]);
		if (access(next_str, X_OK) == 0)
		{
			free(*tab_cmd[0]);
			*tab_cmd[0] = ft_strdup(next_str);
			free(addslash);
			free(next_str);
			return (1);
		}
		i++;
		free(addslash);
		free(next_str);
	}
	return (0);
}

char	**test_exist_fonction(char **tab_cmd, int mode)
{
	char		**pathlist;
	char		*path;
	struct stat	path_stat;

	stat(tab_cmd[0], &path_stat);
	if (ft_strchr(tab_cmd[0], '/') && S_ISREG(path_stat.st_mode) == 0)
		return (NULL);
	if (mode == 2 && (access(tab_cmd[0], F_OK & X_OK) == 0))
	{
		if (tab_cmd[0][0] == '/' || (tab_cmd[0][0] == '.'
					&& tab_cmd[0][1] == '/' && S_ISREG(path_stat.st_mode)))
			return (tab_cmd);
		path = get_env_string("PATH");
		pathlist = ft_strsplit(path, ':');
		if (test_exist_fonction_two(&tab_cmd, pathlist) == 1)
			return (tab_cmd);
	}
	else if (mode == 1)
	{
		path = get_env_string("PATH");
		pathlist = ft_strsplit(path, ':');
		if (test_exist_fonction_two(&tab_cmd, pathlist) == 1)
			return (tab_cmd);
	}
	return (NULL);
}
