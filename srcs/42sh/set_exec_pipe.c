/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:22:41 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		set_fd_before_exec(void)
{
	if (g_tracking.mysh->set_fd->STDIN != 0)
		dup2(g_tracking.mysh->set_fd->STDIN, 0);
	if (g_tracking.mysh->set_fd->STDOUT != 1)
		dup2(g_tracking.mysh->set_fd->STDOUT, 1);
	if (g_tracking.mysh->set_fd->STDERR != 2)
		dup2(g_tracking.mysh->set_fd->STDERR, 2);
}

void		set_new_process(t_jobs *job, pid_t pid0)
{
	new_process(job, pid0);
	if (job->jpid == 0)
		job->jpid = pid0;
	setpgid(pid0, job->jpid);
}

void		close_and_dup(int mode)
{
	if (mode == 1)
	{
		close(descrf_two[0]);
		dup2(descrf_two[1], 1);
		close(descrf_two[1]);
		close(descrf[1]);
		dup2(descrf[0], 0);
		close(descrf[0]);
	}
	else if (mode == 2)
	{
		if (descrf_two[0])
		{
			close(descrf_two[1]);
			dup2(descrf_two[0], 0);
			close(descrf_two[0]);
		}
	}
}

void		set_jobs(t_jobs *job, pid_t pid0)
{
	pid0 = getpid();
	if (job->jpid == 0)
		job->jpid = pid0;
	setpgid(pid0, job->jpid);
	if (job->background == 0)
		tcsetpgrp(g_tracking.sterminal, job->jpid);
	set_process_signal_handlers();
}

void		swap_descrf(void)
{
	if (descrf[0])
	{
		close(descrf[0]);
		close(descrf[1]);
	}
	descrf[0] = descrf_two[0];
	descrf[1] = descrf_two[1];
}
