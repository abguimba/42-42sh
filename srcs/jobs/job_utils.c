/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 22:18:24 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*parse_job_number(char *str)
{
	int			i;
	int			j;
	char		*new;

	i = 1;
	j = 0;
	if (str[0] != '%')
		return (NULL);
	if (!str[1] || (str[i] > 57 || str[i] < 48))
		return (NULL);
	if (!(new = ft_malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	while (str[i])
	{
		while (str[i] == '%')
			i++;
		if (str[i] > 57 || str[i] < 48)
			return (NULL);
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

void			free_job(t_jobs *job)
{
	t_jobs		*tmpelement;
	t_comm		*cmd;
	t_comm		*tmp;

	if (job)
	{
		if (job->prev)
			job->prev->next = job->next ? job->next : NULL;
		if (job->next)
		{
			job->next->prev = job->prev ? job->prev : NULL;
			tmpelement = job->next;
		}
		cmd = job->t_command;
		while (cmd)
		{
			tmp = cmd;
			cmd = cmd->next;
			ft_free(tmp);
		}
		ft_strdel(&job->name);
		ft_free(job);
	}
}

t_comm			*new_process(t_jobs *job, pid_t cpid)
{
	t_comm		*tmp;

	tmp = job->t_command;
	if (job->t_command == NULL)
	{
		if (!(job->t_command = ft_malloc(sizeof(t_comm))))
			return (NULL);
		tmp = job->t_command;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = ft_malloc(sizeof(t_comm))))
			return (NULL);
		tmp = tmp->next;
	}
	tmp->next = NULL;
	tmp->cpid = cpid;
	tmp->done = 0;
	tmp->stopped = 0;
	return (tmp);
}

char			*job_name_maker(t_last *part)
{
	int			len;
	int			spaces;
	t_last		*head;

	len = 0;
	spaces = 0;
	head = part;
	while (part && ft_strcmp(part->name, "&"))
	{
		len = len + ft_strlen(part->name);
		part = part->next;
		spaces++;
	}
	return (job_name_maker_helper(spaces, len, head));
}

t_jobs			*new_job(t_last *part, int background)
{
	t_jobs		*tmp;

	tmp = g_tracking.jobs;
	if (g_tracking.jobs == NULL)
	{
		if (!(g_tracking.jobs = ft_malloc(sizeof(t_jobs))))
			return (NULL);
		tmp = g_tracking.jobs;
		tmp->prev = NULL;
		tmp->place = 1;
	}
	else
		tmp = new_job_helper(tmp);
	getcwd(tmp->wd, 4096);
	tmp->t_command = NULL;
	tmp->current = 0;
	tmp->currentback = 0;
	tmp->next = NULL;
	tmp->jpid = 0;
	tmp->notified = 0;
	tmp->name = job_name_maker(part);
	tmp->startback = background;
	tmp->background = background;
	tmp->backstart = background;
	return (tmp);
}
