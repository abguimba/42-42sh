/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 05:23:25 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		yan_putchar(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

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
	g_tracking.terminfo = ft_malloc(sizeof(t_term_data*));
	g_tracking.myterm = term;
	g_tracking.default_term = default_term;
	get_size();
}
