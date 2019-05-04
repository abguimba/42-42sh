/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_local_env_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/30 22:17:11 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_last			*remove_tmp_env_list(t_last *begin)
{
	t_last		*new;
	t_last		*hold;
	t_last		*head;

	new = create_new_list();
	head = new;
	while (begin && check_if_env(begin->name, 0))
		begin = begin->next;
	new->name = ft_strdup(begin->name);
	begin = begin->next;
	while (begin)
	{
		hold = new;
		new->next = create_new_list();
		new = new->next;
		new->name = ft_strdup(begin->name);
		new->prev = hold;
		new->next = NULL;
		hold->next = new;
		begin = begin->next;
	}
	return (head);
}

t_last			*remove_local_env_list(t_last *begin)
{
	t_last		*new;
	t_last		*hold;
	t_last		*head;

	new = create_new_list();
	head = new;
	while (begin && !its_real_separator(begin))
	{
		begin = begin->next;
	}
	new->name = ft_strdup("true");
	while (begin)
	{
		hold = new;
		new->next = create_new_list();
		new = new->next;
		new->name = ft_strdup(begin->name);
		new->prev = hold;
		new->next = NULL;
		hold->next = new;
		begin = begin->next;
	}
	return (head);
}

int				its_real_separator(t_last *list)
{
	if (ft_strlen(list->name) == 2)
	{
		if (list->name[0] == '|' || list->name[0] == '&')
			return (1);
	}
	else if (list->name[0] == ';' || list->name[0] == '&'
			|| list->name[0] == '|')
		return (1);
	return (0);
}

void			clean_tmp_local_env(void)
{
	t_env	*tmp;
	t_env	*hold;

	tmp = NULL;
	if (g_tracking.mysh->tmpenvsave != NULL)
		tmp = g_tracking.mysh->tmpenvsave;
	else if (g_tracking.mysh->setsave != NULL)
		tmp = g_tracking.mysh->setsave;
	while (tmp)
	{
		hold = tmp;
		tmp = tmp->next;
		ft_strdel(&hold->key);
		ft_strdel(&hold->value);
		free(hold);
	}
}
