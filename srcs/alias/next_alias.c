/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/30 22:32:09 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*new_swap_alias(char *str, int j, int isave, t_keyval *tmp)
{
	char		*new;
	int			len;
	int			i;
	int			l;

	len = ft_strlen(str) - j + ft_strlen(tmp->value);
	if (!(new = ft_malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	l = 0;
	while (str[i] && i < isave)
	{
		new[i] = str[i];
		i++;
	}
	while (tmp->value && tmp->value[l] != '\0')
	{
		new[i] = tmp->value[l];
		i++;
		l++;
	}
	set_alias_globals(tmp->value, l, i);
	swap_alias_helper(new, i - l + j, i, str);
	return (new);
}

char		*verify_if_alias(char *str, int i, t_keyval *tmp, int j)
{
	char	*new;
	char	*alias;
	int		isave;

	alias = tmp->key;
	new = NULL;
	isave = i;
	while (str[i] != '\0' && alias[j] != '\0')
	{
		if (str[i] != alias[j])
			return (NULL);
		i++;
		j++;
	}
	if (!inf_loop(tmp->key, tmp->value, 0, NULL))
		return (new_swap_alias(str, j, isave, tmp));
	return (NULL);
}

char		*check_if_next_alias_helper(char *str, int i)
{
	t_list		*alias;
	t_keyval	*tmp;
	char		*memory;

	if (!g_tracking.mysh->alias_lst)
		return (NULL);
	alias = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	if (!alias)
		return (NULL);
	while (is_spaces(str, i, 1))
		i++;
	while (alias)
	{
		memory = str;
		tmp = alias->content;
		str = verify_if_alias(str, i, tmp, 0);
		if (str != NULL)
			return (str);
		str = memory;
		alias = alias->next;
	}
	return (NULL);
}

int			check_if_next_word(char *str, int i)
{
	int		count;

	count = 0;
	while (str[i] != '\0')
	{
		if (!is_spaces(str, i, 2))
			count++;
		i++;
	}
	return (count);
}

char		*check_if_next_alias(char *str)
{
	int		i;
	char	*memory;

	memory = str;
	i = g_tracking.aliasloop->alias_len;
	if (g_tracking.aliasloop->next_alias && check_if_next_word(str, i))
	{
		g_tracking.aliasloop->next_alias = 0;
		while (str != NULL)
		{
			memory = str;
			str = check_if_next_alias_helper(str, i);
			if (str != NULL)
				ft_strdel(&memory);
		}
		if (g_tracking.aliasloop->next_alias != 0)
		{
			return (check_if_next_alias(memory));
		}
	}
	g_tracking.aliasloop->alias_len = 0;
	return (memory);
}
