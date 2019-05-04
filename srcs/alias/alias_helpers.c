/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/28 08:41:55 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*check_if_first_word_helper(char *str, int isa, int save, int j)
{
	t_list		*hold;
	t_keyval	*t;

	hold = NULL;
	if (g_tracking.mysh->alias_lst)
		hold = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (hold)
	{
		t = hold->content;
		j = 0;
		save = isa;
		while (t->key[j] && str[isa] && str[isa] != '\t'
			&& str[isa] != ' ' && str[isa] != '\r' && str[isa] != '\v'
			&& str[isa] != '\n' && str[isa] == t->key[j])
		{
			j++;
			isa++;
		}
		if (!(t->key[j]) && (!(str[isa]) || (str[isa]
		&& (is_spaces(str, isa, 2)))) && !inf_loop(t->key, t->value, 0, NULL))
			return (swap_alias(str, j, save, t));
		hold = hold->next;
		isa = save;
	}
	return (NULL);
}

char			*check_if_first_word_alias(char *str, int i, int isave)
{
	int		count;

	while (is_spaces(str, i, 2))
		i++;
	while (str[i])
	{
		count = 0;
		if (!is_spaces(str, i, 2))
		{
			isave = i;
			count = 1;
		}
		while (str[i] && !is_spaces(str, i, 2))
		{
			if (str[i] == '=')
				count++;
			i++;
		}
		if (count == 1 && !is_spaces(str, isave, 2))
			return (check_if_first_word_helper(str, isave, 0, 0));
		if (str[i])
			i++;
	}
	return (NULL);
}

void			alias_loop_zero(void)
{
	t_list		*alias;
	t_keyval	*tmp;

	if (!g_tracking.mysh->alias_lst)
		return ;
	alias = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	if (!alias)
		return ;
	while (alias)
	{
		tmp = alias->content;
		if (tmp)
			tmp->loop = 0;
		alias = alias->next;
	}
}

void			print_keyval(t_keyval *tmp)
{
	if (tmp->key)
	{
		ft_putstr(tmp->key);
		ft_putchar('=');
		ft_putchar('\'');
		if (tmp->value)
			ft_putstr(tmp->value);
		ft_putchar('\'');
		ft_putchar('\n');
	}
}
