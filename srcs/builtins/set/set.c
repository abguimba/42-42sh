/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:26:41 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 00:19:10 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		show_setenv(void)
{
	t_list			*tmp;
	t_keyval		*buf;

	ft_env();
	if (!g_tracking.mysh->set_env)
		return (0);
	tmp = g_tracking.mysh->set_env->firstelement;
	buf = NULL;
	while (tmp)
	{
		buf = tmp->content;
		ft_putstr(buf->key);
		ft_putchar('=');
		ft_putendl(buf->value);
		tmp = tmp->next;
	}
	return (0);
}
