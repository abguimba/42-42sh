/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 02:54:31 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int	check_up(void)
{
	int		x;
	int		ab;

	ab = g_tracking.pos->abs;
	x = g_tracking.terminfo->sizex;
	if (ab - x > 0)
		return (0);
	else
		return (1);
}

int	check_down(void)
{
	int		i;
	int		x;
	int		ab;

	ab = g_tracking.pos->abs;
	x = g_tracking.terminfo->sizex;
	i = utf_strlen(g_tracking.str);
	if (ab + x < i)
		return (0);
	else
		return (1);
}
