/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:48:52 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

int					rellocate_cmd(t_last *part, int mode)
{
	while (part && part->check == 1)
		part = part->next;
	if (mode == -1)
	{
		while (part && ft_strcmp(part->name, "||") && ft_strcmp(part->name, ";"))
		{
			part->check = 1;
			part = part->next;
		}
		if (!part)
			return (-1);
		else
		{
			part->check = 1;
			return (0);
		}
	}
	else if (mode == 0)
	{
		while (part && ft_strcmp(part->name, "&&") && ft_strcmp(part->name, ";"))
		{
			part->check = 1;
			part = part->next;
		}
		if (!part)
			return (-1);
		else
		{
			part->check = 1;
			return (0);
		}
	}
	return (0);
}

int					cmd_checker(t_last *part, int mode, t_jobs *job)
{
	if (job->startback == 1)
		return (0);
	if (!(ft_strcmp(check_separator(part), ";")))
		return (0);
	while (part && part->check == 1)
		part = part->next;
	if (!part)
		return (-1);
	if (mode == 0)
	{
		if (!(ft_strcmp(check_separator(part), "&&")))
			return (0);
		return (rellocate_cmd(part, mode));
	}
	else
	{
		if (!(ft_strcmp(check_separator(part), "||")))
			return (0);
		return (rellocate_cmd(part, mode));
	}
}

char				*check_separator(t_last *part)
{
	t_last			*hold;

	while (part && part->check == 1)
	{
		hold = part;
		part = part->next;
	}
	if (part)
		return (part->prev->name);
	else if (hold && ((!(ft_strcmp(hold->name, "||")) ||
		(!(ft_strcmp(hold->name, "&&"))) || (!(ft_strcmp(hold->name, ";"))) ||
		(!(ft_strcmp(hold->name, "&"))))))
		return (hold->name);
	else
		return (NULL);
}

void				free_last(t_last **cmd)
{
	t_last			*tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp->check = 0;
		tmp->type = 0;
		ft_strdel(&tmp->name);
		tmp->prev = NULL;
		tmp = tmp->next;
	}
}
