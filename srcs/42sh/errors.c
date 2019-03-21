/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		argc_error(void)
{
	ft_putendl_fd("usage: ./42sh", 2);
	exit(1);
}

int		exec_errors_dir(char **tab_exec, int mode)
{
	struct stat path_stat;

	stat(g_tracking.g_tab_exec[0], &path_stat);
	if (ft_strchr(g_tracking.g_tab_exec[0], '/') &&
	(access(g_tracking.g_tab_exec[0], F_OK) == 0) && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
		ft_putendl_fd(": is a directory", 2);
		return (-1);
	}
	if (ft_strchr(g_tracking.g_tab_exec[0], '/'))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
		ft_putendl_fd(": no such file or directory", 2);
		return (-1);
	}
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": la commande ", 2);
	ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
	ft_putendl_fd(" n'existe pas", 2);
	return (-1);
}

int		exec_errors(char **tab_exec, int mode)
{
	if (mode == 0)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putendl(": exec format error");
	}
	else if (mode == 1)
	{
		if ((access(g_tracking.g_tab_exec[0], F_OK) == 0) &&
		(access(g_tracking.g_tab_exec[0], X_OK) == -1) &&
		ft_strchr(g_tracking.g_tab_exec[0], '/'))
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(g_tracking.g_tab_exec[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			return (-1);
		}
		exec_errors_dir(tab_exec, mode);
	}
	return (-1);
}
