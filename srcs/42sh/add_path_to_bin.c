/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:00:43 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 05:05:47 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "expansions.h"

int					test_exist_fonction_two(char ***tab_cmd, char **pathlist)
{
	int				i;
	char			*next_str;
	char			*addslash;

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
			ft_free(*tab_cmd[0]);
			*tab_cmd[0] = ft_strdup(next_str);
			ft_free(addslash);
			ft_free(next_str);
			return (1);
		}
		i++;
		ft_free(addslash);
		ft_free(next_str);
	}
	return (0);
}

void				freeing_paths(char *path, char **pathlist)
{
	ft_strdel(&path);
	free_tab(pathlist);
}

char				**exist_help(char **t, char *p, char **pl, struct stat s)
{
	if ((t[0][0] == '/' || (t[0][0] == '.'
	&& t[0][1] == '/')) && S_ISREG(s.st_mode) != 0)
		return (t);
	p = ft_strdup(get_env_string("PATH"));
	pl = ft_strsplit(p, ':');
	if (test_exist_fonction_two(&t, pl) == 1)
	{
		freeing_paths(p, pl);
		return (t);
	}
	freeing_paths(p, pl);
	return (NULL);
}

char				*get_path_value(void)
{
	char			*p;

	p = get_env_string("PATH");
	if (p == NULL)
	{
		p = get_set_env_string("PATH");
		if (p == NULL)
			return (NULL);
		else
			return (ft_strdup(get_set_env_string("PATH")));
	}
	else
		return (ft_strdup(get_env_string("PATH")));
}

char				**test_exist_fonct(char **t_c, int mode, char *p, char **pl)
{
	struct stat		path_stat;

	stat(t_c[0], &path_stat);
	if ((ft_strlen(t_c[0]) == 0) || (t_c[0][0] == '.' && t_c[0][1] == '\0')
	|| (t_c[0][0] == '.' && t_c[0][1] == '.' && t_c[0][2] == '\0'))
		return (NULL);
	if (ft_strchr(t_c[0], '/'))
		if ((stat(t_c[0], &path_stat) == -1) || S_ISREG(path_stat.st_mode) == 0)
			return (NULL);
	if (mode == 1)
	{
		p = get_path_value();
		pl = ft_strsplit(p, ':');
		if (test_exist_fonction_two(&t_c, pl) == 1)
		{
			freeing_paths(p, pl);
			return (t_c);
		}
		freeing_paths(p, pl);
		return (NULL);
	}
	else
		return (exist_help(t_c, p, pl, path_stat));
	freeing_paths(p, pl);
	return (NULL);
}
