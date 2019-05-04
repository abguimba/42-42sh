/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expan_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:32:13 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:35:56 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"
#include "environ.h"

void	ft_lstdelcmd(t_last *el)
{
	if (el)
	{
		if (el->prev)
			el->prev->next = el->next ? el->next : NULL;
		if (el->next)
		{
			el->next->prev = el->prev ? el->prev : NULL;
		}
		if (el->name)
			ft_strdel(&el->name);
		ft_free(el);
		el = NULL;
	}
}

void	re_assign_line(t_last *cmd, t_last **first, t_last *begin)
{
	if (g_tracking.mysh->err_expend == 1)
		return ;
	if ((cmd && cmd->name == NULL) || !ft_strequ(cmd->name, " "))
		*first = begin;
	else if (cmd && ft_strequ(cmd->name, " "))
	{
		ft_lstdelcmd(cmd);
		*first = NULL;
		g_tracking.mysh->err_expend = 0;
	}
	else
	{
		*first = NULL;
		g_tracking.mysh->err_expend = 0;
	}
}

void	re_format_line(t_last **first)
{
	t_last		*next;
	t_last		*prev;
	t_last		*cmd;
	t_last		*begin;

	cmd = *first;
	begin = cmd;
	next = NULL;
	if (!cmd)
		return ;
	next = cmd->next;
	prev = cmd->prev;
	cmd = skip_valid_cmd_obj(cmd);
	if (g_tracking.mysh->err_expend)
	{
		cmd = cut_cmd(cmd, begin, prev, next);
		begin = cmd;
	}
	if (begin)
		re_assign_line(cmd, first, begin);
	else
		*first = NULL;
}

t_last	*chg_env_and_set_vars(t_last *cmd)
{
	if (!cmd->prev || is_sym(cmd->prev->name)
			|| ft_strequ(cmd->prev->name, " "))
	{
		is_to_chg_env(&cmd->name);
		g_tracking.mysh->err_expend = 2;
	}
	cmd = cmd->next;
	return (cmd);
}

t_last	*check_exp_error(t_last *cmd)
{
	t_last		*begin;

	begin = NULL;
	g_tracking.mysh->err_expend = 0;
	begin = cmd;
	while (cmd)
	{
		expand_transformer(&cmd->name, 1);
		cmd = cmd->next;
	}
	cmd = begin;
	if (!cmd)
		return (NULL);
	if (cmd)
		begin = cmd;
	else
		begin = NULL;
	return (begin);
}
