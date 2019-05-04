/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 04:04:23 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		go_home(void)
{
	print_line();
	g_tracking.pos->abs = 0;
	back_to_pos();
}

void		go_end(void)
{
	print_line();
	g_tracking.pos->abs = utf_strlen(g_tracking.str);
	back_to_pos();
}
