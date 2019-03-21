/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		print_alias_lst(void)
{
	t_keyval		*tmp;
	t_list			*buf;

	buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (tmp->key)
				ft_putstr(tmp->key);
			ft_putchar('=');
			if (tmp->value)
				ft_putendl(tmp->value);
		}
		buf = buf->next;
	}
}

char		*return_alias(char *name)
{
	t_keyval		*tmp;
	t_list			*buf;

	if (!g_tracking.mysh->alias_lst || !name)
		return (NULL);
	buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (ft_strcmp(tmp->key, name) == 0)
				return (tmp->value);
		}
		buf = buf->next;
	}
	return (NULL);
}

void		apply_alias(t_last *list)
{
	t_last	*head;
	char	*alias;

	head = list;
	while (head)
	{
		if (head->type == 1)
		{
			alias = return_alias(head->name);
			if (alias)
			{
				free(head->name);
				head->name = ft_strdup(alias);
			}
		}
		head = head->next;
	}
}
