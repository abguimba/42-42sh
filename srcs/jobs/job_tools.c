/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_j_help(int mode, t_jobs *job, t_jobs *hold, t_jobs *hold2)
{
	if (mode == 1)
	{
		if (job->prev == NULL)
		{
			g_tracking.jobs = hold2;
			hold2->prev = NULL;
		}
		if (hold)
			hold->next = hold2;
	}
	else if (mode == 2)
	{
		if (hold2)
			hold2->prev = hold;
		else
			hold->next = NULL;
	}
}

void			free_all_jobs(void)
{
	t_jobs		*tmp;
	t_jobs		*hold;

	tmp = g_tracking.jobs;
	while (tmp)
	{
		hold = tmp;
		tmp = tmp->next;
		free_job(hold);
	}
}

int				suspended_jobs_count(void)
{
	t_jobs		*tmp;
	int			count;

	count = 0;
	tmp = g_tracking.jobs;
	while (tmp)
	{
		if (tmp->t_command)
		{
			if (tmp->t_command->stopped == 1)
				count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

int				job_exists(int place)
{
	t_jobs		*tmp;

	tmp = g_tracking.jobs;
	while (tmp->next)
	{
		if (place == tmp->place)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int				parse_job_sign(char *str)
{
	t_jobs		*tmp;

	tmp = g_tracking.jobs;
	if (!ft_strcmp(str, "\%\%") || !ft_strcmp(str, "\%+"))
	{
		while (tmp->current != 1)
			tmp = tmp->next;
		return (tmp->place);
	}
	else if (!ft_strcmp(str, "\%-"))
	{
		while (tmp && tmp->currentback != 1)
			tmp = tmp->next;
		if (tmp)
			return (tmp->place);
	}
	return (0);
}
