/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 05:52:26 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		jobs_notif_h(t_jobs *job, t_jobs *last, t_jobs *next, int stat)
{
	t_comm	*cmd;

	cmd = job->t_command;
	while (cmd)
	{
		if (!WIFSIGNALED(cmd->status))
		{
			stat = WEXITSTATUS(cmd->status);
			if (job->background == 1)
				show_job_info(job, "Done", 4, stat);
			break ;
		}
		cmd = cmd->next;
		if (job->foreground == 0 && !cmd)
			show_job_info(job, "Killed ", 3, 0);
	}
	if (last)
		last->next = next;
	else
		g_tracking.jobs = next;
	free_job(job);
}

void		jobs_notifications_output(t_jobs *job)
{
	t_comm	*cmd;

	cmd = job->t_command;
	if (job->backstart == 1)
	{
		job->backstart = 0;
		ft_putchar('[');
		ft_putnbr(job->place);
		ft_putchar(']');
		if (job->current == 1)
			ft_putchar('+');
		else if (job->currentback == 1)
			ft_putchar('-');
		else
			ft_putchar(' ');
		ft_putchar(' ');
		if (cmd)
		{
			while (cmd->next)
				cmd = cmd->next;
			ft_putnbr(cmd->cpid);
			ft_putchar('\n');
		}
	}
}

void		show_job_info_helper(t_jobs *job, int mode)
{
	if (mode == 2 || mode == 3 || mode == 4)
	{
		ft_putchar('\n');
		ft_putchar('[');
		ft_putnbr(job->place);
		ft_putchar(']');
	}
	if (mode == 2)
		ft_putchar('+');
	else
	{
		if (job->current == 1)
			ft_putchar('+');
		else if (job->currentback == 1)
			ft_putchar('-');
		else
			ft_putchar(' ');
	}
	ft_putstr("  ");
}
