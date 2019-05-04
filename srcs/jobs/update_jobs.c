/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_jobs		*jobs_update_help(t_jobs *tmp, t_jobs *hold)
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
	return (hold);
}

void		setup_curr_back(t_jobs *tmp, int curr, int back)
{
	tmp->current = curr;
	tmp->currentback = back;
}

void		jobs_updater(t_jobs *tmp, t_jobs *hold)
{
	while (tmp->next)
	{
		setup_curr_back(tmp, 0, 0);
		tmp = tmp->next;
	}
	setup_curr_back(tmp, 0, 0);
	while (tmp)
	{
		if (tmp->t_command->stopped == 1)
		{
			if (hold == NULL)
			{
				setup_curr_back(tmp, 1, 0);
				hold = tmp->prev;
			}
			else
				return (setup_curr_back(tmp, 0, 1));
		}
		if (!tmp->prev)
			break ;
		tmp = tmp->prev;
	}
	setup_curr_back(hold, 1, 0);
}

void		jobs_update_currentback(int mode)
{
	t_jobs	*tmp;
	t_jobs	*hold;

	tmp = g_tracking.jobs;
	hold = NULL;
	if (!tmp->next)
		return (setup_curr_back(tmp, 1, 0));
	else if (mode == 1)
		hold = jobs_update_help(tmp, hold);
	else if (mode > 1)
		jobs_updater(tmp, hold);
}

void		jobs_update_current(void)
{
	t_jobs	*tmp;
	t_jobs	*hold;

	tmp = g_tracking.jobs;
	hold = NULL;
	if (tmp)
	{
		if (suspended_jobs_count() == 0)
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
			jobs_update_currentback(suspended_jobs_count());
	}
}
