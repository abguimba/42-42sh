/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 03:05:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 05:09:10 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		single_key(char c)
{
	if (c == K_BKSP)
	{
		rem_from_str();
		return (12);
	}
	if (c == K_CTRLR)
	{
		begin_search();
		return (12);
	}
	if (c == 10 || c == 13)
	{
		ft_return();
		return (13);
	}
	if (c == K_TAB)
	{
		auto_complete();
		return (12);
	}
	return (ctrl_key(c));
}

int		check(char *str)
{
	if (ft_strncmp(str, "\x1b\x5b", 2) == 0
	|| ft_strncmp(str, "\x1b\x4f", 2) == 0)
		return (1);
	return (0);
}

int		get_key(void)
{
	int		flag;

	flag = 0;
	g_tracking.fc = 0;
	if (g_tracking.interactive == 1)
		tcsetattr(0, TCSANOW, &g_tracking.myterm);
	get_coolprompt();
	init_str();
	if (g_tracking.interactive == 1)
		print_prompt();
	g_tracking.histindex = get_last() + 1;
	if (g_tracking.linemode == 0)
		while (readloop(0, STDIN_FILENO, NULL) == 0)
		{
		}
	else
		flag = basic_mode();
	if (g_tracking.interactive == 1)
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
	set_shell_signal_handlers();
	if (flag == 0)
		return (1);
	else
		return (flag);
}
