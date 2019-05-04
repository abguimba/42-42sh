/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 00:19:04 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			ft_env(void)
{
	t_list		*hold;
	t_keyval	*tmp;

	hold = NULL;
	if (g_tracking.mysh->env)
		hold = g_tracking.mysh->env->firstelement;
	while (hold)
	{
		tmp = hold->content;
		ft_putstr(tmp->key);
		ft_putchar('=');
		ft_putendl(tmp->value);
		hold = hold->next;
	}
	return (0);
}
