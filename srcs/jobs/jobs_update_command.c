/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_update_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 02:30:25 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!update_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

int			update_st_help(t_jobs *job, pid_t pid, t_comm *cmd, int status)
{
	if (job)
	{
		while (job)
		{
			cmd = job->t_command;
			while (cmd)
			{
				if (cmd->cpid == pid)
				{
					cmd->status = status;
					if (WIFSTOPPED(status))
						cmd->stopped = 1;
					else
						cmd->done = 1;
				}
				cmd = cmd->next;
			}
			job = job->next;
		}
		return (0);
	}
	else
		return (job_control_errors(pid, 1, -1));
}

int			update_process_status(pid_t pid, int status)
{
	t_jobs	*job;
	t_comm	*cmd;

	cmd = NULL;
	job = g_tracking.jobs;
	if (pid > 0)
		return (update_st_help(job, pid, cmd, status));
	else if (pid == 0)
		return (-1);
	else
		return (-1);
}
