/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 00:22:44 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				put_job_in_foreground(t_jobs *job, int cont)
{
	job->foreground = 1;
	tcsetpgrp(g_tracking.sterminal, job->jpid);
	if (cont)
	{
		if (job->startback != 1)
			tcsetattr(g_tracking.sterminal, TCSADRAIN, &job->jterm);
		kill(-job->jpid, SIGCONT);
	}
	wait_for_job(job);
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
	tcgetattr(g_tracking.sterminal, &job->jterm);
	job->startback = 0;
}

void				put_job_in_background(t_jobs *job, int cont)
{
	job->foreground = 0;
	if (cont)
		kill(-job->jpid, SIGCONT);
	else
		g_tracking.lastbackground = job->jpid;
}

void				interactive_check_set_shell_group(void)
{
	g_tracking.sterminal = STDIN_FILENO;
	g_tracking.interactive = isatty(g_tracking.sterminal);
	if (g_tracking.interactive)
	{
		while (tcgetpgrp(g_tracking.sterminal) != (g_tracking.spid = getpgrp()))
			kill(-g_tracking.spid, SIGTTIN);
	}
	g_tracking.spid = getpid();
	if (setpgid(g_tracking.spid, g_tracking.spid) < 0)
	{
		ft_putendl_fd("Couldn't put the shell in its own process group", 2);
		ft_exit2(EXIT_FAILURE);
	}
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
}

int					job_is_done(t_jobs *job)
{
	t_comm			*p;

	p = job->t_command;
	while (p)
	{
		if (p->done == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int					job_is_stopped(t_jobs *job)
{
	t_comm			*p;

	p = job->t_command;
	while (p)
	{
		if (p->stopped == 0)
			return (0);
		p = p->next;
	}
	return (1);
}
