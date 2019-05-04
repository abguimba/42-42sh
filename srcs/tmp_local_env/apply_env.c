/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 01:39:55 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_set_env(char *key, char *value)
{
	if (get_env_string(key))
	{
		replace_env_str(key, value);
		update_envp();
	}
	else
	{
		replace_env_set_str(key, value);
	}
}

void		init_tmp_env(char *key, char *value)
{
	replace_env_str(key, value);
}

void		apply_env_and_del_path(void)
{
	t_env	*tmp;

	tmp = NULL;
	if (g_tracking.mysh->tmpenvsave != NULL)
	{
		tmp = g_tracking.mysh->tmpenvsave;
		while (tmp)
		{
			init_tmp_env(tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else if (g_tracking.mysh->setsave != NULL)
	{
		tmp = g_tracking.mysh->setsave;
		while (tmp)
		{
			init_set_env(tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}

void		apply_env(void)
{
	t_env	*tmp;

	tmp = NULL;
	if (g_tracking.mysh->tmpenvsave != NULL)
	{
		tmp = g_tracking.mysh->tmpenvsave;
		while (tmp)
		{
			init_tmp_env(tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else if (g_tracking.mysh->setsave != NULL)
	{
		tmp = g_tracking.mysh->setsave;
		while (tmp)
		{
			init_set_env(tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}
