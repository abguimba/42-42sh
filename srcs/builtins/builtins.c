/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/21 13:38:00 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int			is_builtin(void)
{
	if (ft_builtin_search("jobs") || ft_builtin_search("fg")
		|| ft_builtin_search("bg") || ft_builtin_search("exit")
		|| ft_builtin_search("set") || ft_builtin_search("echo")
		|| ft_builtin_search("hash") || ft_builtin_search("test")
		|| ft_builtin_search("cd") || ft_builtin_search("history")
		|| ft_builtin_search("alias") || ft_builtin_search("unalias"))
		return (1);
	return (0);
}

int			is_builtin_alone(void)
{
	t_jobs	*tmp;
	int		i;

	i = 0;
	tmp = g_tracking.jobs;
	if (!(is_builtin()))
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->name[i] != '\0')
	{
		if (tmp->name[i] == '|')
			return (0);
		i++;
	}
	return (1);
}

int			ft_builtin_search(char *builtin)
{
	char	*tmp;
	int		i;

	tmp = g_tracking.g_tab_exec[0];
	i = 0;
	while (tmp[i] && (tmp[i] == '\'' || tmp[i] == '\"'))
		i++;
	while (*builtin && *builtin == tmp[i])
	{
		builtin++;
		i++;
	}
	if (*builtin == '\0' && tmp[i] == '\0')
		return (1);
	return (0);
}

int			builtin_exec(void)
{
	if (ft_builtin_search("jobs"))
		return (jobs_builtin());
	else if (ft_builtin_search("fg"))
		return (fg_builtin());
	else if (ft_builtin_search("bg"))
		return (bg_builtin());
	else if (ft_builtin_search("set"))
		return (show_setenv());
	else if (ft_builtin_search("echo"))
		return (check_and_exec_echo());
	else if (ft_builtin_search("exit"))
		return (ft_exit());
	else if (ft_builtin_search("hash"))
		return (ft_hash());
	else if (ft_builtin_search("test"))
		return (main_test(1));
	else if (ft_builtin_search("cd"))
		return (ft_cd());
	else if (ft_builtin_search("history"))
		return (history());
	else if (ft_builtin_search("alias"))
		return (add_alias());
	else if (ft_builtin_search("unalias"))
		return (unalias_blt());
	return (0);
}
