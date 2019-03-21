/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 00:27:30 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	get_size(void)
{
	struct winsize	ts;
	int				col;
	int				row;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &ts);
	col = (ts.ws_col);
	row = (ts.ws_row);
	g_tracking.terminfo->sizex = col;
	g_tracking.terminfo->sizey = row;
}
