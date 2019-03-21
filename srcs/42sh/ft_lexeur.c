/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:41:13 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 17:15:21 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		error_lexer(t_last *list_cmd)
{
	if (!list_cmd)
		return (1);
	while (list_cmd)
	{
		if (list_cmd->type == OP && !list_cmd->next)
		{
			write(2, "42sh:syntax error near unexpected token `newline'\n", 51);
			return (1);
		}
		else if (list_cmd->type == OP && list_cmd->next
				&& (list_cmd->next->type == SEP || list_cmd->next->type == OP))
		{
			ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
			ft_putstr_fd(list_cmd->next->name, 2);
			ft_putendl_fd("'", 2);
			return (1);
		}
		else
			list_cmd = list_cmd->next;
	}
	return (0);
}
