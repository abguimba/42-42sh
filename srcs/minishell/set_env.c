/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 23:54:07 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:41:56 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_tab_path_two(t_tab *st_tab, char **env)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		str = ft_strndup(env[i], 5);
		if (ft_strcmp(str, "PATH=") == 0)
		{
			free(str);
			st_tab->tab_path = ft_strsplit(&env[i++][5], ':');
			while (st_tab->tab_path[j])
			{
				str = ft_strjoin(st_tab->tab_path[j], "/");
				free(st_tab->tab_path[j]);
				st_tab->tab_path[j++] = str;
			}
			return ;
		}
		else
			free(str);
	}
	st_tab->tab_path = NULL;
}

int		test_arg_two(t_tab *st_tab, char **temp_env, int j)
{
	int		i;
	pid_t	father;
	char	*next_str;

	i = 0;
	while (st_tab->tab_path && st_tab->tab_path[i])
	{
		next_str = ft_strjoin(st_tab->tab_path[i], st_tab->tab_word[j]);
		if (access(next_str, X_OK) == 0)
		{
			father = fork();
			if (father == 0)
				execve(next_str, &st_tab->tab_word[j], temp_env);
			free(next_str);
			wait(&father);
			forfree(st_tab->tab_path);
			return (1);
		}
		else
		{
			free(next_str);
			i++;
		}
	}
	return (0);
}

int		test_arg(t_tab *st_tab, char **temp_env, int j)
{
	char	*next_str;
	int		i;
	int		test_proc;
	pid_t	father;

	i = 0;
	if (access(st_tab->tab_word[1], X_OK) == 0)
	{
		father = fork();
		if (father == 0)
			execve(st_tab->tab_word[j], &st_tab->tab_word[j], temp_env);
		wait(&father);
		return (1);
	}
	else
	{
		create_tab_path_two(st_tab, temp_env);
		if (test_arg_two(st_tab, temp_env, j) == 1)
			return (1);
	}
	ft_dprintf(2, "env: %s: %s\n", st_tab->tab_word[j],
			"No such file or directory");
	return (1);
}

void	affich_env(t_env *st_env, t_tab *st_tab)
{
	int		i;
	int		ret;
	char	**temp_env;

	i = 1;
	ret = 0;
	temp_env = duplicate_env(st_env->env);
	if (st_tab->tab_word[1] && ft_strcmp(st_tab->tab_word[1], "-i") != 0)
	{
		while (st_tab->tab_word[i] && check_is_env(st_tab->tab_word[i]) == 1)
		{
			if ((existe_env(temp_env, st_tab->tab_word[i]) == 1))
				modif_env(temp_env, st_tab->tab_word[i]);
			else if ((existe_env(temp_env, st_tab->tab_word[i]) == 0))
				create_env(&temp_env, st_tab->tab_word[i]);
			i++;
		}
		ret = (st_tab->tab_word[i] ? test_arg(st_tab, temp_env, i) : 1);
	}
	forfree(temp_env);
	i = 0;
	if (ret == 0)
		while (st_env->env[i])
			ft_printf("%s\n", st_env->env[i++]);
}

void	set_env(t_env *st_env, char **env)
{
	int		i;

	i = 0;
	st_env->env = malloc(sizeof(char *) * nb_env(env));
	while (env[i])
	{
		st_env->env[i] = ft_strdup(env[i]);
		i++;
	}
	st_env->env[i] = NULL;
}
