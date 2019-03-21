/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 05:23:25 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 03:16:14 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	check_term(char *name)
{
	int			a;
	char		buf[1024];

	if (!name)
		return ;
	a = tgetent(buf, name);
	g_tracking.linemode = 0;
	if (a == 0)
		ft_putendl("No such entry in terminal database");
	if (a == -1)
		ft_putendl("Terminfo database could not be found");
	if (a != 1)
	{
		ft_putendl("switching to basic line mode");
		g_tracking.linemode = 1;
	}
}

int		clear_screen3(void)
{
	char	*res;

	back_home();
	if ((res = tgetstr("cd", NULL)) == NULL)
		return (-1);
	tputs(res, 1, yan_putchar);
	return (0);
}

int		clear_screen2(void)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-1);
	tputs(res, 1, yan_putchar);
	return (0);
}

void	get_term(void)
{
	char			*name_term;
	struct termios	term;
	struct termios	default_term;

	if (!(name_term = getenv("TERM")))
	{
		ft_putendl("No terminal found in ENV");
		ft_putendl("switching to basic line mode");
		g_tracking.linemode = 1;
	}
	check_term(name_term);
	tcgetattr(0, &default_term);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	g_tracking.terminfo = malloc(sizeof(t_term_data*));
	g_tracking.myterm = term;
	g_tracking.default_term = default_term;
	get_size();
}
