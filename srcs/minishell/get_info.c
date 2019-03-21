/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 06:33:22 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:41:43 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_last_pwd(char **env)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	while (env[i])
	{
		str = ft_strndup(env[i], 7);
		if (ft_strcmp(str, "OLDPWD=") == 0)
		{
			free(str);
			temp = ft_strdup(&env[i][7]);
			return (temp);
		}
		i++;
		free(str);
	}
	return (NULL);
}

char	*get_pwd(char **env)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	while (env[i])
	{
		str = ft_strndup(env[i], 4);
		if (ft_strcmp(str, "PWD=") == 0)
		{
			free(str);
			temp = ft_strdup(&env[i][4]);
			return (temp);
		}
		i++;
		free(str);
	}
	return (NULL);
}

char	*get_home(char **env)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	while (env[i])
	{
		str = ft_strndup(env[i], 5);
		if (ft_strcmp(str, "HOME=") == 0)
		{
			free(str);
			temp = ft_strdup(&env[i][5]);
			return (temp);
		}
		i++;
		free(str);
	}
	return (NULL);
}

void	change_pwd(char ***env, char *pwd)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	while ((*env)[i])
	{
		str = ft_strndup((*env)[i], 4);
		if (ft_strcmp(str, "PWD=") == 0)
		{
			free((*env)[i]);
			free(str);
			(*env)[i] = ft_strjoin("PWD=", pwd);
			return ;
		}
		i++;
		free(str);
	}
	temp = ft_strjoin("PWD=", pwd);
	create_env(env, temp);
	free(temp);
}

void	change_last_pwd(char **env, char *pwd)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i])
	{
		str = ft_strndup(env[i], 7);
		if (ft_strcmp(str, "OLDPWD=") == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", pwd);
		}
		i++;
		free(str);
	}
}
