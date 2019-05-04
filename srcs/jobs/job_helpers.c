/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 02:42:07 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		is_still_atty(void)
{
	int		sterminal;
	int		isinteractive;

	sterminal = STDIN_FILENO;
	isinteractive = isatty(sterminal);
	if (isinteractive)
	{
		while (tcgetpgrp(sterminal) != (g_tracking.spid = getpgrp()))
			kill(-g_tracking.spid, SIGTTIN);
	}
}

t_jobs		*new_job_helper(t_jobs *tmp)
{
	int		i;
	t_jobs	*hold;

	i = 2;
	hold = NULL;
	while (tmp->next)
	{
		hold = tmp;
		tmp = tmp->next;
		i++;
	}
	hold = tmp;
	if (!(tmp->next = ft_malloc(sizeof(t_jobs))))
		return (NULL);
	tmp = tmp->next;
	if (hold->next && hold == tmp)
		tmp->prev = hold->next;
	else
		tmp->prev = hold;
	tmp->place = hold->place + 1;
	return (tmp);
}

char		*job_name_maker_helper(int spaces, int len, t_last *head)
{
	char	*new;

	if (!(new = ft_malloc(sizeof(char) * (len + spaces + 1))))
		return (NULL);
	len = 0;
	while (head && ft_strcmp(head->name, "&"))
	{
		spaces = 0;
		while (head->name[spaces] != '\0')
		{
			new[len] = head->name[spaces];
			len++;
			spaces++;
		}
		if (head->next)
			new[len++] = ' ';
		head = head->next;
	}
	new[len] = '\0';
	return (new);
}

void		wait_for_job_helper(int status, t_jobs *job)
{
	if (WIFSIGNALED(status))
	{
		g_tracking.expandreturn = 128 + WTERMSIG(status);
		set_expand_return();
	}
	else
	{
		g_tracking.expandreturn = 128 + WSTOPSIG(status);
		job->foreground = 0;
	}
	g_tracking.lastreturn = g_tracking.expandreturn + 128;
}

void		wait_for_job(t_jobs *job)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!update_process_status(pid, status) && !job_is_stopped(job)
			&& !job_is_done(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	if (WIFSIGNALED(status) || WIFSTOPPED(status))
		wait_for_job_helper(status, job);
	else if (WIFEXITED(status))
	{
		g_tracking.lastreturn = WEXITSTATUS(status);
		g_tracking.expandreturn = g_tracking.lastreturn;
	}
	else
	{
		g_tracking.lastreturn = 1;
		g_tracking.expandreturn = 1;
	}
}
