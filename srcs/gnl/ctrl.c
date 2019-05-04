/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 00:53:23 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 07:38:02 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ctrl_d(void)
{
	if (g_tracking.quotes != 0)
	{
		if (g_tracking.quotes == 1 || g_tracking.quotes == 2)
		{
			ft_putendl_fd("Unexpected EOF while looking for matching \"\'", 2);
			ft_putchar('\n');
		}
		g_tracking.quotes = 10;
		return ;
	}
	if (utf_strlen(g_tracking.str) == 0)
	{
		ft_putchar('\n');
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		ft_exit2(EXIT_SUCCESS);
	}
	else
		rem_from_str_del();
}

void	ctrl_c(void)
{
	ft_free(g_tracking.cpaste->line);
	if (g_tracking.quotes == 3)
	{
		ft_putchar('\n');
		g_tracking.quotes = 11;
		return ;
	}
	if (g_tracking.quotes != 0)
	{
		ft_putchar('\n');
		g_tracking.quotes = 10;
		return ;
	}
	if (g_tracking.tmp_hist)
		ft_strdel(&g_tracking.tmp_hist);
	ft_strdel(&g_tracking.str);
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
	if ((c > 0 && c < 32) && c != 27)
		return (12);
	return (0);
}
