/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/30 16:49:53 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_new_tmp_env(t_env *tmp, char *str)
{
	t_env	*hold;

	if (g_tracking.mysh->tmpenvsave == NULL)
	{
		if (!(g_tracking.mysh->tmpenvsave = malloc(sizeof(t_env))))
			return ;
		g_tracking.mysh->tmpenvsave->next = NULL;
		g_tracking.mysh->tmpenvsave->key = init_local_env_key(str, 0, 0);
		g_tracking.mysh->tmpenvsave->value = init_local_env_value(str, 0, 0);
	}
	else
	{
		tmp = g_tracking.mysh->tmpenvsave;
		while (tmp)
		{
			hold = tmp;
			tmp = tmp->next;
		}
		if (!(hold->next = malloc(sizeof(t_env))))
			return ;
		tmp = hold->next;
		tmp->next = NULL;
		tmp->key = init_local_env_key(str, 0, 0);
		tmp->value = init_local_env_value(str, 0, 0);
	}
}

void		save_tmp_vars(t_last *begin)
{
	t_env	*tmp;

	tmp = NULL;
	while (begin && check_if_env(begin->name, 0))
	{
		init_new_tmp_env(tmp, begin->name);
		begin = begin->next;
	}
}
