/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:41:13 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:09:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_sym(char *str)
{
	if (ft_strequ(str, "&&")
		|| ft_strequ(str, "||")
		|| ft_strequ(str, ";")
		|| ft_strequ(str, "|")
		|| ft_strequ(str, "&"))
		return (1);
	return (0);
}

int		error_begin_line(t_last *list_cmd)
{
	t_last	*cmd;

	cmd = list_cmd;
	while (cmd)
	{
		if (!cmd->prev && (ft_strequ(cmd->name, "&&")
			|| ft_strequ(cmd->name, "||")
			|| ft_strequ(cmd->name, ";")
			|| ft_strequ(cmd->name, "|")
			|| ft_strequ(cmd->name, "&")))
		{
			put_unexpected_token(cmd->name);
			return (1);
		}
		else if (cmd && cmd->next && is_sym(cmd->name)
			&& is_sym(cmd->next->name))
		{
			put_unexpected_token(cmd->name);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int		tokken_error(t_last *list_cmd, int i)
{
	if (i == 1)
	{
		write(2, "42sh:syntax error near unexpected token `newline'\n", 51);
		return (-1);
	}
	else
	{
		ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
		ft_putstr_fd(list_cmd->next->name, 2);
		ft_putendl_fd("'", 2);
	}
	return (-1);
}

int		error_lexer(t_last *list_cmd)
{
	char	*name;

	name = NULL;
	if (!list_cmd || error_begin_line(list_cmd))
		return (-1);
	while (list_cmd)
	{
		if (list_cmd->type == OP && !list_cmd->next)
			return (tokken_error(list_cmd, 1));
		else if (list_cmd->type == OP && list_cmd->next
				&& (list_cmd->next->type == SEP
				|| list_cmd->next->type == OP))
			return (tokken_error(list_cmd, 0));
		else if (list_cmd->type == OP && its_heredoc(list_cmd->name))
		{
			if (!(name = exec_create_heredoc(list_cmd->next->name)))
				return (-1);
			ft_strdel(&list_cmd->next->name);
			list_cmd->next->name = name;
			list_cmd = list_cmd->next;
		}
		else
			list_cmd = list_cmd->next;
	}
	return (0);
}
