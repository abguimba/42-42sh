/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 06:10:07 by mjose             #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

char	*get_parm_string(char *str)
{
	t_env_set	*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->setenv_lst == NULL)
		return (NULL);
	tmp = g_tracking.mysh->setenv_lst;
	while (tmp && tmp->param && !ft_strequ(tmp->param->key, str))
		tmp = tmp->next;
	if (tmp && tmp->param && tmp->param->value)
		return (ft_strdup(tmp->param->value));
	return (NULL);
}

int		is_to_add_or_mod_parm(char *to_transf)
{
	int		i;

	i = 0;
	while (to_transf[i])
	{
		if (to_transf[i] == '$')
			return (0);
		if (to_transf[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		have_parm(char *to_transf)
{
	int		i;
	int		to;

	i = 0;
	while (to_transf[i])
	{
		if (to_transf[i] == '$' && to_transf[i + 1] == '{')
		{
			to = i;
			while (to_transf[to])
			{
				if (to_transf[to] == '}')
					return (1);
				to++;
			}
		}
		i++;
	}
	return (0);
}
