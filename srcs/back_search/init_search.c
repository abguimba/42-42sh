/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:53:39 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 05:15:11 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		back_up(int y, int i, int winx)
{
	winx = g_tracking.terminfo->sizex;
	if (g_tracking.found)
		i = utf_strlen(g_tracking.found);
	else
		i = ft_strlen("No such string in history");
	i = i + ft_strlen("(back-i-search) :_ ::");
	i = i + ft_strlen(g_tracking.search);
	y = i / winx;
	y++;
	if (ft_strlen(g_tracking.search) < 1)
	{
		g_tracking.histindex = get_last() + 1;
		tputs(tgetstr("cr", NULL), 1, yan_putchar);
		tputs(tgetstr("cd", NULL), 1, yan_putchar);
		ft_putstr("(back-i-search) :");
	}
	if (i % winx == 0)
		y--;
	tputs(tgetstr("cr", NULL), 1, yan_putchar);
	while (y != 0)
	{
		y--;
		tputs(tgetstr("up", NULL), 1, yan_putchar);
	}
}

int			ft_return_key(void)
{
	if (g_tracking.found)
	{
		ft_bzero(g_tracking.str, g_tracking.buffsize);
		g_tracking.pos->abs = 0;
		ft_strdel(&g_tracking.search);
		add_to_str(ft_strdup(g_tracking.found));
	}
	else
	{
		ft_strdel(&g_tracking.search);
		print_line();
		back_to_pos();
	}
	g_tracking.histindex = get_last() + 1;
	g_tracking.found = NULL;
	g_tracking.search = NULL;
	return (1);
}

int			read_search(void)
{
	char	c;

	c = 0;
	read(STDERR_FILENO, &c, 1);
	if (c == 10)
		return (ft_return_key());
	if (c == 18)
	{
		if (g_tracking.histindex > 1)
			g_tracking.histindex--;
	}
	if (c == 127)
	{
		g_tracking.histindex = get_last() + 1;
		ft_putnbr(g_tracking.histindex);
		if (ft_strlen(g_tracking.search) > 0)
			g_tracking.search = ft_strsub(g_tracking.search, 0,
			(ft_strlen(g_tracking.search) - 1), 1);
		return (0);
	}
	if (c < 32)
		return (2);
	tputs(tgetstr("le", NULL), 1, yan_putchar);
	g_tracking.search = ft_strjoinchar(g_tracking.search, c, 1);
	return (0);
}

int			begin_search(void)
{
	int		y;

	g_tracking.search = ft_strnew(0);
	y = 0;
	tputs(tgetstr("do", NULL), 1, yan_putchar);
	ft_putstr("(back-i-search) :");
	tputs(tgetstr("up", NULL), 1, yan_putchar);
	while (read_search() != 1)
	{
		tputs(tgetstr("do", NULL), 1, yan_putchar);
		tputs(tgetstr("cd", NULL), 1, yan_putchar);
		ft_putstr("(back-i-search) :");
		ft_putstr(g_tracking.search);
		ft_putstr("_ ::");
		g_tracking.found = get_hist_ptr(g_tracking.search);
		if (!g_tracking.found)
			ft_putstr("No such string in history");
		else
			ft_putstr(g_tracking.found);
		back_up(0, 0, 0);
	}
	ft_strdel(&g_tracking.search);
	g_tracking.search = NULL;
	return (0);
}
