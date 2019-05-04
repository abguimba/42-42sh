/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_cursor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 03:49:52 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			back_up_add(void)
{
	int			y;
	int			ab;

	ab = utf_strlen(g_tracking.str);
	ab += g_tracking.pos->prompt;
	ab--;
	ab += utf_strlen(g_tracking.aut->to_add);
	y = ab / g_tracking.terminfo->sizex;
	y = y - (g_tracking.pos->y);
	g_tracking.aut->to_add_y = y;
	while (y > 0)
	{
		y--;
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
	}
	tputs(tgetstr("cr ", NULL), 1, yan_putchar);
}

void			go_back_down(void)
{
	int			y;
	int			ab;

	ab = utf_strlen(g_tracking.str);
	ab += g_tracking.pos->prompt;
	ab--;
	ab += utf_strlen(g_tracking.aut->to_add);
	y = ab / g_tracking.terminfo->sizex;
	y = y - (g_tracking.pos->y);
	while (y > 0)
	{
		y--;
		tputs(tgetstr("do ", NULL), 1, yan_putchar);
	}
}
