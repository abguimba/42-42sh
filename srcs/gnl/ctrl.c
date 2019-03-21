/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 00:53:23 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ctrl_d(void)
{
	if (g_tracking.quotes == 1)
	{
		ft_putchar('\n');
		ft_putendl_fd("Unexpected EOF while looking for matching \"\'", 2);
		g_tracking.quotes = 10;
		return ;
	}
	if (utf_strlen(g_tracking.str) == 0)
	{
		ft_putchar('\n');
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		ft_exit();
	}
	else
		rem_from_str_del();
}

void	ctrl_c(void)
{
	free(g_tracking.str);
	free(g_tracking.cpaste->line);
	free(g_tracking.cpaste);
	g_tracking.str = NULL;
	cursor_reset();
}

int		ctrl_key(char c)
{
	if (c == 04)
	{
		ctrl_d();
		if (g_tracking.quotes == 10)
			return (13);
		else
			return (12);
	}
	if (c == 03)
	{
		ctrl_c();
		return (13);
	}
	return (0);
}
