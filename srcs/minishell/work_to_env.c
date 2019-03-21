/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 03:20:55 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:42:07 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_env(char *str)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
		{
			temp = ft_strndup(str, i + 1);
			return (temp);
		}
		i++;
	}
	return (NULL);
}

void	create_env(char ***env, char *str)
{
	int		i;

	i = 0;
	(*env) = duplicate_tab(env);
	while ((*env)[i])
		i++;
	(*env)[i] = ft_strdup(str);
}

void	delete_env(char ***env, char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*env)[i])
	{
		temp = ft_strndup((*env)[i], ft_strlen(str));
		if (ft_strcmp(temp, str) == 0 && (*env)[i][ft_strlen(str)] == '=')
		{
			(*env) = duplicate_tab_two(env, i);
			free(temp);
			return ;
		}
		free(temp);
		i++;
	}
	return ;
}

void	modif_env(char **env, char *str)
{
	int		i;
	char	*search;
	char	*temp;

	i = 0;
	if ((search = search_env(str)))
	{
		while (env[i])
		{
			temp = ft_strndup(env[i], ft_strlen(search));
			if (ft_strcmp(temp, search) == 0)
			{
				free(env[i]);
				free(temp);
				free(search);
				env[i] = ft_strdup(str);
				return ;
			}
			free(temp);
			i++;
		}
		free(search);
	}
	return ;
}

int		existe_env(char **env, char *str)
{
	int		i;
	char	*search;
	char	*temp;

	i = 0;
	if ((search = search_env(str)))
	{
		while (env[i])
		{
			temp = ft_strndup(env[i], ft_strlen(search));
			if (ft_strcmp(temp, search) == 0)
			{
				free(temp);
				free(search);
				return (1);
			}
			free(temp);
			i++;
		}
		free(search);
		return (0);
	}
	return (-1);
}
