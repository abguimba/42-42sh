/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 03:42:52 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_last	*ret_error(char *line)
{
	ft_strdel(&line);
	return (NULL);
}

int		argc_error(void)
{
	ft_putendl_fd("usage: ./42sh [-t] [testfile]", 2);
	exit(1);
}

int		exec_errors_cont(void)
{
	if (ft_strchr(g_tracking.g_tab_exec[0], '/')
	&& access(g_tracking.g_tab_exec[0], F_OK == -1))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
		ft_putendl_fd(": no such file or directory", 2);
		return (1);
	}
	else if (access(g_tracking.g_tab_exec[0], F_OK) == 0
	&& access(g_tracking.g_tab_exec[0], X_OK) == 0
	&& g_tracking.g_tab_exec[0][0] == '.')
		exec_sh();
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": command ", 2);
	ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
	ft_putendl_fd(" not found", 2);
	return (127);
}

int		exec_errors_dir(void)
{
	struct stat path_stat;

	stat(g_tracking.g_tab_exec[0], &path_stat);
	if (g_tracking.g_tab_exec[0][0] == '.'
	&& g_tracking.g_tab_exec[0][1] == '\0')
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
		ft_putendl_fd(": filename argument required", 2);
		return (2);
	}
	if (ft_strchr(g_tracking.g_tab_exec[0], '/')
		&& (access(g_tracking.g_tab_exec[0], F_OK) == 0)
		&& S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
		ft_putendl_fd(": is a directory", 2);
		return (126);
	}
	return (exec_errors_cont());
}

int		exec_errors(char **tab_exec, int mode)
{
	(void)tab_exec;
	if (mode == 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putendl(": exec format error");
	}
	else if (mode == 1)
	{
		if ((access(g_tracking.g_tab_exec[0], F_OK) == 0)
			&& (access(g_tracking.g_tab_exec[0], X_OK) == -1)
			&& ft_strchr(g_tracking.g_tab_exec[0], '/'))
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			return (127);
		}
		return (exec_errors_dir());
	}
	return (1);
}
