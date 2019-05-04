/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:32:13 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 04:21:18 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"
#include "environ.h"

t_last		*run_to_next_cmd(t_last *cmd, t_last *next)
{
	if (next && cmd)
		cmd = cmd->next;
	else
		cmd = NULL;
	return (cmd);
}

t_last		*check_for_local_vars(t_last *list_cmd)
{
	t_last	*begin;

	begin = NULL;
	begin = list_cmd;
	while (list_cmd)
		list_cmd = chg_env_and_set_vars(list_cmd);
	list_cmd = begin;
	re_format_line(&list_cmd);
	return (list_cmd);
}
