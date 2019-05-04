/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/29 07:28:17 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_alias_exists(t_keyval *tmp)
{
	t_list		*hold;
	t_keyval	*holdcontent;

	hold = NULL;
	if (g_tracking.mysh->alias_lst)
		hold = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	else
		return (1);
	while (hold)
	{
		holdcontent = hold->content;
		if (!ft_strcmp(holdcontent->key, tmp->key))
		{
			lstcontainer_remove(g_tracking.mysh->alias_lst, hold, 1);
			return (1);
		}
		hold = hold->next;
	}
	return (1);
}

int		alias_or_orig(char *orig, char *value, int i, char *key)
{
	int		isave;
	int		j;

	(void)orig;
	isave = i;
	j = check_if_used_alias(value, i, 0);
	if (j == -1)
		return (-1);
	j = 0;
	while (value[isave] != '\0' && key[j] != '\0')
	{
		if (value[isave] != key[j])
			break ;
		isave++;
		j++;
	}
	if (value[isave] == '\0' && key[j] == '\0')
		return (0);
	return (1);
}

int		check_if_last_word(char *aliasvalue, int i)
{
	int		isave;

	isave = i;
	if (!aliasvalue[i])
		return (i);
	while (aliasvalue[i] != '\0')
	{
		if (!is_spaces(aliasvalue, i, 2))
			return (isave - 1);
		i++;
	}
	return (i - 1);
}

int		next_separateur_loop(char *aliasvalue, int i)
{
	while (aliasvalue[i] != '\0')
	{
		while (aliasvalue[i] && !is_spaces(aliasvalue, i, 2))
			i++;
		while (aliasvalue[i] && aliasvalue[i] != '&' && aliasvalue[i] != '|'
		&& aliasvalue[i] != ';')
			i++;
		if (aliasvalue[i])
		{
			while (aliasvalue[i] && (aliasvalue[i] == '&'
			|| aliasvalue[i] == ';' || aliasvalue[i] == '|'))
				i++;
			while (aliasvalue[i] && is_spaces(aliasvalue, i, 1))
				i++;
			return (check_if_last_word(aliasvalue, i));
		}
	}
	return (i - 1);
}

int		inf_loop(char *origkey, char *aliasval, int i, t_list *hold)
{
	int			nb;
	t_keyval	*tmp;

	add_used_alias(origkey);
	if (g_tracking.mysh->alias_lst)
		hold = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (hold)
	{
		tmp = hold->content;
		i = 0;
		while (aliasval && aliasval[i] != '\0')
		{
			if (aliasval[i] && !is_spaces(aliasval, i, 2))
			{
				if ((nb = alias_or_orig(origkey, aliasval, i, tmp->key)) == -1)
					return (clean_used_alias(1));
				else if (nb == 0)
					return (inf_loop(tmp->key, tmp->value, 0, NULL));
				i = next_separateur_loop(aliasval, i);
			}
			i = (aliasval[i]) ? i + 1 : i;
		}
		hold = hold->next;
	}
	return (clean_used_alias(0));
}
