/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 06:24:58 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			size_of_key_or_val(char *str, int mode, int count, int i)
{
	if (mode == 1)
	{
		while (str[i] != '=')
		{
			count++;
			i++;
		}
	}
	else
	{
		while (str[i] != '=')
			i++;
		i++;
		while (str[i] != '\0')
		{
			if (str[i] != '\"' && str[i] != '\'')
				count++;
			i++;
		}
	}
	return (count);
}

char		*init_local_env_value(char *str, int i, int j)
{
	int		len;
	char	*new;

	len = size_of_key_or_val(str, 2, 0, 0);
	if (len == 0)
		return (ft_strdup(""));
	if (!(new = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[i] != '=')
		i++;
	i++;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char		*init_local_env_key(char *str, int i, int j)
{
	int		len;
	char	*new;

	len = size_of_key_or_val(str, 1, 0, 0);
	if (!(new = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[i] != '=')
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}

void		init_new_local_env(t_env *tmp, char *str)
{
	t_env	*hold;

	if (g_tracking.mysh->setsave == NULL)
	{
		if (!(g_tracking.mysh->setsave = malloc(sizeof(t_env))))
			return ;
		g_tracking.mysh->setsave->next = NULL;
		g_tracking.mysh->setsave->key = init_local_env_key(str, 0, 0);
		g_tracking.mysh->setsave->value = init_local_env_value(str, 0, 0);
	}
	else
	{
		tmp = g_tracking.mysh->setsave;
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

void		save_local_vars(t_last *begin)
{
	t_env	*tmp;

	tmp = NULL;
	while (begin && !its_real_separator(begin))
	{
		init_new_local_env(tmp, begin->name);
		begin = begin->next;
	}
}
