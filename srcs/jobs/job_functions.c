/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		jobs_update_currentback(int mode)
{
	t_jobs	*tmp;
	t_jobs	*hold;

	tmp = g_tracking.jobs;
	hold = NULL;
	if (!tmp->next)
	{
		tmp->current = 1;
		tmp->currentback = 0;
		return ;
	}
	else if (mode == 1)
	{
		while (tmp->next)
		{
			tmp->current = 0;
			tmp->currentback = 0;
			tmp = tmp->next;
		}
		while (tmp->prev && tmp->t_command->stopped != 1)
			tmp = tmp->prev;
		tmp->current = 1;
		tmp->currentback = 0;
		if (tmp->next)
		{
			hold = tmp->next;
			while (hold->next)
				hold = hold->next;
		}
		else
			hold = tmp->prev;
	}
	else if (mode > 1)
	{
		while (tmp->next)
		{
			tmp->current = 0;
			tmp->currentback = 0;
			tmp = tmp->next;
		}
		tmp->current = 0;
		tmp->currentback = 0;
		while (tmp)
		{
			if (tmp->t_command->stopped == 1)
			{
				if (hold == NULL)
				{
					tmp->current = 1;
					tmp->currentback = 0;
					hold = tmp->prev;
				}
				else
				{
					tmp->current = 0;
					tmp->currentback = 1;
					return ;
				}
			}
			if (!tmp->prev)
				break ;
			tmp = tmp->prev;
		}
	}
	hold->current = 0;
	hold->currentback = 1;
}

void		jobs_update_current(void)
{
	t_jobs	*tmp;
	int		mode;
	t_jobs	*hold;

	tmp = g_tracking.jobs;
	hold = NULL;
	mode = suspended_jobs_count();
	if (tmp)
	{
		if (mode == 0)
		{
			while (tmp->next)
			{
				tmp->current = 0;
				tmp->currentback = 0;
				hold = tmp;
				tmp = tmp->next;
			}
			tmp->currentback = 0;
			if (hold != NULL)
				hold->currentback = 1;
			tmp->current = 1;
		}
		else
			jobs_update_currentback(mode);
	}
}

void		mark_job_as_running(t_jobs *job)
{
	t_comm	*cmd;

	cmd = job->t_command;
	while (cmd)
	{
		cmd->stopped = 0;
		cmd = cmd->next;
	}
	job->notified = 0;
}

void		continue_job(t_jobs *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_job_in_foreground(job, 1);
	else
		put_job_in_background(job, 1);
}

void		jobs_notifications(void)
{
	t_jobs	*job;
	t_jobs	*joblast;
	t_jobs	*jobnext;
	t_comm	*cmd;

	update_status();
	joblast = NULL;
	job = g_tracking.jobs;
	while (job)
	{
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
			ft_putnbr(job->jpid);
			ft_putchar('\n');
		}
		jobnext = job->next;
		if (job_is_done(job))
		{
			if (job->background == 1)
			{
				cmd = job->t_command;
				while (cmd)
				{
					if (!WIFSIGNALED(cmd->status))
					{
						show_job_info(job, "Done           ", 1);
						break ;
					}
					cmd = cmd->next;
					if (!cmd)
					{
						show_job_info(job, "Killed ", 3);
					}
				}
			}
			if (joblast)
				joblast->next = jobnext;
			else
				g_tracking.jobs = jobnext;
			free_job(job);
		}
		else if (job_is_stopped(job) && !job->notified)
		{
			show_job_info(job, "Stopped                ", 2);
			job->notified = 1;
			joblast = job;
		}
		else
			joblast = job;
		job = jobnext;
	}
}

void		show_job_info(t_jobs *job, const char *status, int mode)
{
	if (mode)
	{
		if (mode == 2 || mode == 3)
		ft_putchar('\n');
		ft_putchar('[');
		ft_putnbr(job->place);
		ft_putchar(']');
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
	else
	{
		ft_putnbr(job->jpid);
		ft_putstr("   ");
	}
	ft_putstr(status);
	if (mode == 3)
	{
		ft_putstr("by signal: ");
		ft_putnbr(WTERMSIG(job->t_command->status));
	}
	ft_putchar(' ');
	ft_putendl(job->name);
}

void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!update_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

int			update_process_status(pid_t pid, int status)
{
	t_jobs	*job;
	t_comm	*cmd;

	if (pid > 0)
    {
		job = g_tracking.jobs;
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
		{
			fprintf (stderr, "No child process %d.\n", pid);
			return (-1);
		}
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	else 
		return (-1);
}

void		wait_for_job(t_jobs *job)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!update_process_status(pid, status) && !job_is_stopped(job) &&
	!job_is_done(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	g_tracking.lastreturn = WEXITSTATUS(status);
}

void				put_job_in_foreground(t_jobs *job, int cont)
{
	tcsetpgrp(g_tracking.sterminal, job->jpid);
	if (cont)
	{
		// kill(job->jpid, SIGTTIN);
		// tcsetattr(g_tracking.sterminal, TCSADRAIN, &job->jterm);
		if (kill (- job->jpid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	wait_for_job(job);
	tcsetpgrp(g_tracking.sterminal, g_tracking.spid);
	tcgetattr(g_tracking.sterminal, &job->jterm);
	// tcsetattr(g_tracking.sterminal, TCSADRAIN, &g_tracking.myterm);
}

void				put_job_in_background(t_jobs *job, int cont)
{
	if (cont)
	{
		if (kill (-job->jpid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
}

void				interactive_check_set_shell_group(void)
{
	g_tracking.sterminal = STDIN_FILENO;
	g_tracking.interactive = isatty(g_tracking.sterminal);
	if (g_tracking.interactive)
	{
	while (tcgetpgrp(g_tracking.sterminal) != (g_tracking.spid = getpgrp()))
		kill(- g_tracking.spid, SIGTTIN);
	}
	g_tracking.spid = getpid();
	if (setpgid(g_tracking.spid, g_tracking.spid) < 0)
	{
    	ft_putendl_fd("Couldn't put the shell in its own process group", 2);
		exit(1);
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
