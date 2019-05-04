/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_local_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 06:11:28 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_last		*find_local_vars(t_last *begin)
{
	t_last	*new;

	save_local_vars(begin);
	new = remove_local_env_list(begin);
	convert_list(new);
	return (new);
}

t_last		*find_tmpenv_vars(t_last *begin)
{
	t_last	*new;

	save_tmp_vars(begin);
	new = remove_tmp_env_list(begin);
	convert_list(new);
	return (new);
}

int			check_if_env(char *str, int i)
{
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$')
			return (0);
		i++;
	}
	if (str[i] == '=' && i > 0 && !is_spaces(str, i - 1, 1))
		return (1);
	return (0);
}

t_last		*tmp_local_vars(t_last *begin, t_last *beginsave)
{
	int		mode;

	clean_tmp_local_env();
	g_tracking.mysh->tmpenvsave = NULL;
	g_tracking.mysh->setsave = NULL;
	if ((mode = check_if_env(begin->name, 0)))
	{
		begin = begin->next;
		while (begin && !its_real_separator(begin))
		{
			if (!check_if_env(begin->name, 0))
			{
				mode = 2;
				break ;
			}
			begin = begin->next;
		}
		if (mode == 1)
			return (find_local_vars(beginsave));
		else
			return (find_tmpenv_vars(beginsave));
	}
	return (NULL);
}
