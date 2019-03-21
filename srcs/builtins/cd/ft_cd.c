/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:17:02 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_parsecd(char **av, char *option)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_strcmp(av[i], "-") == 0)
			return (i);
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'P' || av[i][1] == 'L')
				*option = av[i][1];
			if (av[i][1] == '-')
			{
				i++;
				return (i);
			}
			if (av[i][1] != 'P' && av[i][1] != 'L'
			&& av[i][1] != '-')
				return (i);
		}
		if (av[i][0] != '-')
			return (i);
		i++;
	}
	return (i);
}

void	ft_changedir(char option, char *path)
{
	char	*truepwd;
	char	*oldpwd;
	char	*newpwd;

	if (getright(path) == 0)
	{
		truepwd = ft_true_pwd();
		replace_env_str("TRUEOLDPWD", truepwd);
		oldpwd = ft_strdup(get_env_string("PWD"));
		chdir(path);
		if (option != 'P')
			replace_env_str("PWD", path);
		else
		{
			free(truepwd);
			truepwd = ft_true_pwd();
			replace_env_str("PWD", truepwd);
		}
		replace_env_str("OLDPWD", oldpwd);
		free(truepwd);
		truepwd = NULL;
		free(oldpwd);
	}
}

char	*buildpath(char option, char *path)
{
	char	*pwd;
	int		i;

	pwd = NULL;
	if (option == 'P')
		pwd = ft_true_pwd();
	else
		pwd = ft_strdup(get_env_string("PWD"));
	if (pwd == NULL)
		pwd = ft_true_pwd();
	i = ft_strlen(pwd);
	if (pwd[i] != '/')
		pwd = ft_strjoinfree(pwd, "/", 1);
	if (path[0] != '/')
		path = ft_strjoinfree(pwd, path, 2);
	path = ft_dot(path);
	free(pwd);
	return (path);
}

int		ft_cd2(char option, int i, char *path)
{
	if (ft_strlen(path) == 0)
		ft_putendl("cd: HOME not set");
	if (ft_strlen(path) == 0)
		return (0);
	if (ft_strcmp(path, "/") == 0)
	{
		ft_changedir(option, path);
		return (0);
	}
	path = ft_homepath(path);
	if (path[0] != '.' && path[0] != '/')
		path = ft_cdpath(path);
	if (option != 'P')
		path = buildpath(option, path);
	ft_changedir(option, path);
	if (i == 875)
		ft_putendl(path);
	free(path);
	return (0);
}

int		ft_cd(void)
{
	char			*path;
	char			**av;
	char			option;
	int				i;

	option = 'P';
	av = g_tracking.g_tab_exec;
	i = ft_parsecd(av, &option);
	path = NULL;
	if (!av[i] || ft_strcmp(av[i], "~") == 0)
		path = ft_strdup(get_env_string("HOME"));
	else
		path = ft_strdup((av[i]));
	if (ft_strcmp(av[i], "-") == 0)
	{
		i = 875;
		free(path);
		path = ft_strdup(get_env_string("OLDPWD"));
		if (ft_strlen(path) == 0)
		{
			ft_putendl("OLDPWD not set");
			return (0);
		}
	}
	return (ft_cd2(option, i, path));
}
