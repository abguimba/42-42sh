/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:26:48 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	update_pos(void)
{
	int	ab;

	ab = g_tracking.pos->abs + g_tracking.pos->prompt;
	g_tracking.pos->x = ab % g_tracking.terminfo->sizex;
	g_tracking.pos->legacy = (utf_strlen(g_tracking.str)
	+ g_tracking.pos->prompt) / g_tracking.terminfo->sizex;
}

void	back_home(void)
{
	int	y;

	y = g_tracking.pos->y;
	while (y > 0)
	{
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
		y--;
	}
	tputs(tgetstr("cr ", NULL), 1, yan_putchar);
}

void	move_to_end(void)
{
	int		x;
	int		i;

	x = g_tracking.terminfo->sizex - 1;
	i = 0;
	tputs(tgetstr("up", NULL), 1, yan_putchar);
	tputs(tgetstr("cr", NULL), 1, yan_putchar);
	while (i < x)
	{
		tputs(tgetstr("nd", NULL), 1, yan_putchar);
		i++;
	}
	g_tracking.pos->y--;
}

void	move_cursor(int i, int x, int ab)
{
	int		flag;

	flag = 0;
	if (x == 0)
		tputs(tgetstr("do", NULL), 1, yan_putchar);
	while (ab > i)
	{
		flag = 0;
		x = (ab % g_tracking.terminfo->sizex);
		if (x == 0)
		{
			move_to_end();
			ab--;
			flag = 1;
		}
		if (flag == 0)
		{
			tputs(tgetstr("le", NULL), 1, yan_putchar);
			ab--;
		}
	}
}

void	back_to_pos(void)
{
	int		i;
	int		x;
	int		ab;

	ab = utf_strlen(g_tracking.str);
	ab += g_tracking.pos->prompt;
	g_tracking.pos->y = ab / g_tracking.terminfo->sizex;
	i = g_tracking.pos->abs + g_tracking.pos->prompt;
	x = (ab % g_tracking.terminfo->sizex);
	move_cursor(i, x, ab);
}
