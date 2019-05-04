/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 03:12:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			errors_hash(char *binary, int error)
{
	if (error == 0)
		ft_putendl_fd(SHELL_NAME": hash table empty", 2);
	if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME": hash: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putendl_fd(" not found", 2);
	}
	if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME": hash: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putendl_fd(" invalid option", 2);
		ft_putendl_fd(SHELL_NAME": hash: usage: hash [-r] [arg]", 2);
	}
	return (2);
}

int			errors_fg(int nb, int error, char *hold)
{
	if (error == 1)
		ft_putendl_fd(SHELL_NAME": fg: only one job supported", 2);
	if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME": fg: ", 2);
		ft_putendl_fd("wrong job_id usage", 2);
		return (2);
	}
	else if (error == 3)
	{
		ft_putstr_fd(SHELL_NAME": fg: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" doesn't exist!", 2);
	}
	else if (error == 4)
		ft_putendl_fd(SHELL_NAME": fg: no jobs!", 2);
	else if (error == 5)
		ft_putendl_fd(SHELL_NAME": fg: no job control!", 2);
	ft_strdel(&hold);
	return (2);
}

int			errors_bg(int nb, int error, char *hold)
{
	if (error == 0)
	{
		ft_putstr_fd(SHELL_NAME": bg: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" is already in the background!", 2);
	}
	else if (error == 1)
		ft_putendl_fd(SHELL_NAME": bg: only one job supported", 2);
	else if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME ": bg: ", 2);
		ft_putendl_fd("wrong job_id usage", 2);
	}
	else if (error == 3)
	{
		ft_putstr_fd(SHELL_NAME": bg: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" doesn't exist!", 2);
	}
	else if (error == 4)
		ft_putendl_fd(SHELL_NAME": bg: no jobs!", 2);
	else if (error == 5)
		ft_putendl_fd(SHELL_NAME": bg: no job control!", 2);
	ft_strdel(&hold);
	return (2);
}

void		ft_error_job_1(void)
{
	ft_putstr_fd(SHELL_NAME": jobs: ", 2);
	ft_putendl_fd("wrong options usage", 2);
	ft_putendl_fd("jobs: usage: jobs [-lp] [\%jobid ...]", 2);
}

int			errors_jobs(char option, int nb, int error)
{
	if (error == 0)
		ft_error_job_1();
	else if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME": jobs: -", 2);
		ft_putchar_fd(option, 2);
		ft_putstr_fd(": invalid option", 2);
		ft_putendl_fd("jobs: usage: jobs [-lp] [\%jobid ...]", 2);
	}
	else if (error == 2)
	{
		ft_putstr_fd(SHELL_NAME": jobs: job ", 2);
		ft_putnbr_fd(nb, 2);
		ft_putendl_fd(" doesn't exist!", 2);
	}
	if (error == 3)
	{
		ft_putstr_fd(SHELL_NAME": jobs: ", 2);
		ft_putendl_fd("wrong job_id usage", 2);
		return (2);
	}
	else if (error == 4)
		ft_putendl_fd(SHELL_NAME": jobs: no jobs!", 2);
	return (2);
}
