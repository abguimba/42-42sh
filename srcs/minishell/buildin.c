/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 06:37:34 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 20:35:05 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unsetenv(t_env *st_env, t_tab *st_tab)
{
	if (!st_tab->tab_word[1])
		return ;
	else if (ft_strcmp(st_tab->tab_word[1], "*") == 0)
		freetab(st_env->env);
	else
		delete_env(&st_env->env, st_tab->tab_word[1]);
}

void	ft_setenv(t_env *st_env, t_tab *st_tab)
{
	if (!st_tab->tab_word[1])
		return ;
	else
	{
		if ((existe_env(st_env->env, st_tab->tab_word[1]) == 1))
			modif_env(st_env->env, st_tab->tab_word[1]);
		else if ((existe_env(st_env->env, st_tab->tab_word[1]) == 0))
			create_env(&st_env->env, st_tab->tab_word[1]);
		else
			return ;
	}
}

void	ft_echo(t_tab *st_tab, t_env *st_env)
{
	int		i;

	i = 1;
	if (!st_tab->tab_word[i])
		ft_putchar('\n');
	while (st_tab->tab_word[i])
	{
		if (st_tab->tab_word[i][0] == '$')
		{
			search_and_affich_env(&st_tab->tab_word[i][1], st_env->env);
			i++;
		}
		else
			ft_printf("%s", st_tab->tab_word[i++]);
		if (st_tab->tab_word[i])
			ft_putchar(' ');
		else
			ft_putchar('\n');
	}
}

void	ft_cd_two(t_tab *st_tab, t_env *st_env, char *pwd, char *buf)
{
	if (st_tab->tab_word[2] && st_tab->tab_word[1][0] == '-'
			&& st_tab->tab_word[1][1] == 'L')
	{
		change_last_pwd(st_env->env, pwd);
		modif_pwd(st_env->env, st_tab->tab_word[2]);
		chdir(st_tab->tab_word[2]);
	}
	else if (st_tab->tab_word[2])
	{
		chdir(st_tab->tab_word[2]);
		change_last_pwd(st_env->env, pwd);
		free(pwd);
		pwd = getcwd(buf, SIZE_MAX);
		change_pwd(&st_env->env, pwd);
	}
	else
	{
		chdir(st_tab->tab_word[1]);
		change_last_pwd(st_env->env, pwd);
		pwd = getcwd(buf, SIZE_MAX);
		change_pwd(&st_env->env, pwd);
	}
}

void	ft_cd(t_env *st_env, t_tab *st_tab)
{
	char	*pwd;
	char	*old_pwd;
	char	*buf;

	buf = NULL;
	pwd = getcwd(buf, SIZE_MAX);
	if (!st_tab->tab_word[1] || (ft_strcmp(st_tab->tab_word[1], "~") == 0))
	{
		change_last_pwd(st_env->env, pwd);
		change_pwd(&st_env->env, "/Users/alsomvil/");
		chdir("/Users/alsomvil/");
	}
	else if (st_tab->tab_word[1][0] == '$')
		chdir(recup_path(st_env->env, &st_tab->tab_word[1][1]));
	else if (ft_strcmp(st_tab->tab_word[1], "-") == 0)
	{
		old_pwd = get_last_pwd(st_env->env);
		chdir(old_pwd);
		change_last_pwd(st_env->env, pwd);
		change_pwd(&st_env->env, old_pwd);
		free(old_pwd);
	}
	else
		ft_cd_two(st_tab, st_env, pwd, buf);
	free(pwd);
}
