/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 04:27:31 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	run_to_first_invalid(t_last **cur)
{
	t_last	*cmd;

	cmd = *cur;
	while (cmd && !is_sym(cmd->name))
	{
		if (cmd && cmd->prev)
			cmd = cmd->prev;
		else
			break ;
	}
	*cur = cmd;
}

void	rmv_cur_cmd(t_last **cur_cmd)
{
	t_last		*next;
	t_last		*prev;
	t_last		*cmd;
	t_last		*begin;

	begin = *cur_cmd;
	cmd = begin;
	if (cmd && g_tracking.mysh->err_expend)
	{
		prev = cmd->prev;
		while (cmd && (ft_strequ(cmd->name, " ") || is_sym(cmd->name)))
		{
			next = cmd->next;
			ft_lstdelcmd(cmd);
			cmd = next;
			if (cmd)
				cmd->prev = prev;
		}
		if (!prev)
			begin = cmd;
	}
	if (begin)
		*cur_cmd = begin;
	else
		*cur_cmd = NULL;
}

t_last	*skip_valid_cmd_obj(t_last *cmd)
{
	while (cmd && g_tracking.mysh->err_expend == 1)
	{
		if (ft_strequ(cmd->name, " ") && g_tracking.mysh->err_expend)
		{
			run_to_first_invalid(&cmd);
			break ;
		}
		cmd = cmd->next;
	}
	return (cmd);
}

t_last	*cut_cmd(t_last *cmd, t_last *begin, t_last *prev, t_last *next)
{
	while (cmd)
	{
		if (ft_strequ(cmd->name, " "))
		{
			next = cmd->next;
			prev = cmd->prev;
			rmv_cur_cmd(&cmd);
			if (!prev)
				return (NULL);
			else
				cmd = begin;
		}
		if (cmd)
			cmd = cmd->next;
	}
	cmd = begin;
	return (cmd);
}
