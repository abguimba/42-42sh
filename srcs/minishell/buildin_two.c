/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 15:07:37 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 20:35:44 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	search_and_affich_env(char *tab, char **env)
{
	char	*temp;
	int		i;

	i = 0;
	while (env[i])
	{
		temp = ft_strndup(env[i], ft_strlen(tab));
		if (ft_strcmp(tab, temp) == 0 && env[i][ft_strlen(tab)] == '=')
		{
			ft_printf("%s", &env[i][ft_strlen(tab) + 1]);
		}
		free(temp);
		i++;
	}
}

int		check_is_builtins(t_tab *st_tab)
{
	if (ft_strcmp(st_tab->tab_word[0], "echo") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "cd") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "setenv") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "unsetenv") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "alias") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "unalias") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "alias_print") == 0 ||
			ft_strcmp(st_tab->tab_word[0], "env") == 0)
		return (1);
	return (0);
}

void	realize_built(t_tab *st_tab, t_env *st_env, char **line, char **env)
{
	char	*path;
	char	*buf;
	char	*pwd;
	char	*home;

	buf = NULL;
	if (ft_strcmp(st_tab->tab_word[0], "env") == 0)
		affich_env(st_env, st_tab);
	else if (ft_strcmp(st_tab->tab_word[0], "echo") == 0)
		ft_echo(st_tab, st_env);
	else if (ft_strcmp(st_tab->tab_word[0], "cd") == 0)
		ft_cd(st_env, st_tab);
	else if (ft_strcmp(st_tab->tab_word[0], "setenv") == 0)
		ft_setenv(st_env, st_tab);
	else if (ft_strcmp(st_tab->tab_word[0], "unsetenv") == 0)
		ft_unsetenv(st_env, st_tab);
	else if (ft_strcmp(st_tab->tab_word[0], "alias") == 0)
		add_alias(st_tab->tab_word[1]);
	else if (ft_strcmp(st_tab->tab_word[0], "alias_print") == 0)
		print_alias_lst();
	else if (ft_strcmp(st_tab->tab_word[0], "unalias") == 0)
		unalias(st_tab->tab_word[1]);
}

char	*recup_path(char **env, char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
	{
		temp = ft_strndup(env[i], ft_strlen(str));
		if (ft_strcmp(str, temp) == 0 && env[i][ft_strlen(str)] == '=')
		{
			free(temp);
			return (&env[i][ft_strlen(str) + 1]);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

void	modif_pwd(char **env, char *str)
{
	char		*temp;
	char		*buf;
	char		*fuck;
	struct stat	test;
	char		*tp;

	buf = NULL;
	fuck = getcwd(buf, SIZE_MAX);
	tp = ft_strjoin("/", str);
	temp = ft_strjoin(fuck, tp);
	lstat(temp, &test);
	if (S_ISLNK(test.st_mode))
		change_pwd(&env, temp);
	free(fuck);
	free(tp);
	free(temp);
}
