/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

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
	if (!(new = malloc(sizeof(char) * (ft_strlen(str)))))
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
	t_jobs		*hold;
	t_comm		*tmp;
	t_jobs		*hold2;
	t_comm		*cmd;

	hold = NULL;
	hold2 = NULL;
	if (job->prev)
		hold = job->prev;
	if (job->next)
		hold2 = job->next;
	cmd = job->t_command;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	ft_strdel(&job->name);
	if (hold2)
	{
		if (job->prev == NULL)
		{
			g_tracking.jobs = hold2;
			hold2->prev = NULL;
		}
		if (hold)
			hold->next = hold2;
	}
	if (hold)
	{
		if (hold2)
			hold2->prev = hold;
		else
			hold->next = NULL;
	}
	free(job);
	if (!hold && !hold2)
		g_tracking.jobs = NULL;
}

t_comm			*new_process(t_jobs *job, pid_t cpid)
{
	t_comm		*tmp;

	if (job->t_command == NULL)
	{
		if (!(job->t_command = malloc(sizeof(t_comm))))
			return (NULL);
		job->t_command->next = NULL;
		job->t_command->cpid = cpid;
		job->t_command->done = 0;
		job->t_command->stopped = 0;
	}
	else
	{
		tmp = job->t_command;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = malloc(sizeof(t_comm))))
			return (NULL);
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->cpid = cpid;
		tmp->done = 0;
		tmp->stopped = 0;
	}
	return (tmp);
}

char			*job_name_maker(t_last *part)
{
	int			len;
	int			spaces;
	char		*new;
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
	if (!(new = malloc(sizeof(char) * (len + spaces + 1))))
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
	return(new);
}

t_jobs			*new_job(t_last *part, int background)
{
	t_jobs		*tmp;
	t_jobs		*hold;
	int			i;

	i = 2;
	if (g_tracking.jobs == NULL)
	{
		if (!(g_tracking.jobs = malloc(sizeof(t_jobs))))
			return (NULL);
		tmp = g_tracking.jobs;
		getcwd(tmp->wd, 4096);
		tmp->t_command = NULL;
		tmp->prev = NULL;
		tmp->current = 0;
		tmp->currentback = 0;
		tmp->next = NULL;
		tmp->jpid = 0;
		tmp->notified = 0;
		tmp->name = job_name_maker(part);
		tmp->place = 1;
		tmp->startback = background;
		tmp->background = background;
		tmp->backstart = background;
	}
	else
	{
		tmp = g_tracking.jobs;
		while (tmp->next)
		{
			hold = tmp;
			tmp = tmp->next;
			i++;
		}
		hold = tmp;
		if (!(tmp->next = malloc(sizeof(t_jobs))))
			return (NULL);
		tmp = tmp->next;
		tmp->next = NULL;
		if (hold->next && hold == tmp)
			tmp->prev = hold->next;
		else
			tmp->prev = hold;
		tmp->t_command = NULL;
		tmp->jpid = 0;
		tmp->notified = 0;
		tmp->current = 0;
		tmp->currentback = 0;
		tmp->name = job_name_maker(part);
		getcwd(tmp->wd, 4096);
		tmp->place = hold->place + 1;
		tmp->background = background;
		tmp->startback = background;
		tmp->backstart = background;
	}
	return (tmp);
}
