/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/28 08:36:22 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		set_alias_globals(char *value, int i, int j)
{
	if (!value)
	{
		g_tracking.aliasloop->alias_len = 0;
		g_tracking.aliasloop->next_alias = 0;
		return ;
	}
	else
	{
		g_tracking.aliasloop->alias_len = j;
		if (i > 0 && value[i - 1] == ' ')
			g_tracking.aliasloop->next_alias = 1;
		else
			g_tracking.aliasloop->next_alias = 0;
	}
}

int			check_if_used_alias(char *str, int i, int j)
{
	int			isave;
	t_alias		*tmp;

	tmp = NULL;
	if (g_tracking.aliasloop)
		tmp = g_tracking.aliasloop;
	isave = i;
	while (tmp && tmp->alias)
	{
		i = isave;
		j = 0;
		while (str[i] != '\0' && tmp->alias[j] != '\0')
		{
			if (str[i] != tmp->alias[j])
				break ;
			i++;
			j++;
		}
		if (tmp->alias[j] == '\0' && (str[i] == '\0' || is_spaces(str, i, 1)))
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int			clean_used_alias(int returncode)
{
	t_alias		*tmp;
	t_alias		*hold;

	tmp = NULL;
	if (g_tracking.aliasloop)
		tmp = g_tracking.aliasloop;
	if (tmp)
	{
		ft_strdel(&tmp->alias);
		tmp = tmp->next;
	}
	while (tmp)
	{
		hold = tmp;
		tmp = tmp->next;
		ft_strdel(&hold->alias);
		free(hold);
	}
	g_tracking.aliasloop->alias = NULL;
	g_tracking.aliasloop->next = NULL;
	return (returncode);
}

void		add_used_alias(char *alias)
{
	t_alias		*tmp;
	t_alias		*hold;

	tmp = g_tracking.aliasloop;
	while (tmp && tmp->alias != NULL)
	{
		hold = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		if (!(hold->next = ft_malloc(sizeof(t_alias))))
			return ;
		hold = hold->next;
		hold->alias = ft_strdup(alias);
		hold->next = NULL;
	}
	else
		tmp->alias = ft_strdup(alias);
}
