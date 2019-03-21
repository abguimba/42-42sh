/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 04:12:58 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_line(void)
{
	if (g_tracking.str != NULL)
	{
		clear_screen3();
		print_prompt();
		ft_putstr_fd(g_tracking.str, 0);
	}
}

void	print_line_cpy(int start, int end)
{
	int		i;

	start = g_tracking.cpaste->b1;
	end = g_tracking.cpaste->b2;
	i = 0;
	if (end < start)
	{
		start = g_tracking.cpaste->b2;
		end = g_tracking.cpaste->b1;
	}
	start = utf_goto(g_tracking.str, start);
	end = utf_goto(g_tracking.str, end);
	clear_screen3();
	print_prompt();
	while (g_tracking.str[i])
	{
		if (i == start)
			ft_putstr_fd("\033[7m", 0);
		if (i == end)
			ft_putstr_fd("\033[0m", 0);
		ft_putchar_fd(g_tracking.str[i], 0);
		i++;
	}
	ft_putstr_fd("\033[0m", 0);
	back_to_pos();
}
