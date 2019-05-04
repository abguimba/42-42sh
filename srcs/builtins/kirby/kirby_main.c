/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kirby_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 22:51:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 05:35:58 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		too_soon(char buf)
{
	if (buf == 'l')
	{
		ft_putendl_fd("Player 2 drew too soon. P1 WINS !", 2);
		sleep(2);
	}
	if (buf == 's')
	{
		ft_putendl_fd("Player 1 drew too soon. P2 WINS !", 2);
		sleep(2);
	}
	if (set_kirby_screen() != 0)
		return (-1);
	if (buf == 27)
		return (-1);
	return (-3);
}

int		print_usage(void)
{
	char	c;

	c = 65;
	ft_putendl("Player one press: s");
	ft_putendl("Player one press: l");
	ft_putendl("press enter or spacebar to start a new game");
	while (c != 10 && c != 27 && c != 32)
		read(0, &c, 1);
	if (c == 10 || c == 32)
		return (0);
	if (c == 27)
		return (1);
	return (1);
}

int		exit_kirby(void)
{
	char	c;
	int		flag;

	c = 65;
	ft_putendl("Are you sure you want to quit ?   Y/N");
	while (c != 89 && c != 121 && c != 110 && c != 78)
		read(0, &c, 1);
	if (c == 89 || c == 121)
		flag = 1;
	else
		flag = 0;
	return (flag);
}

int		k_main(void)
{
	int		flag;

	flag = 0;
	if (g_tracking.interactive != 1)
		return (0);
	tcsetattr(0, TCSANOW, &g_tracking.myterm);
	tputs(tgetstr("vi", NULL), 1, yan_putchar);
	tputs(tgetstr("ti", NULL), 1, yan_putchar);
	while (game_loop() == 0)
	{
	}
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
	tputs(tgetstr("te", NULL), 1, yan_putchar);
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	if (flag == -1)
		ft_putendl_fd("Temsize too small", 2);
	if (flag < 0)
		return (2);
	return (exit_kirby());
}

int		special_main(void)
{
	int		i;
	char	*test;

	test = get_file(1);
	if (test == NULL)
	{
		ft_strdel(&test);
		ft_putendl_fd("Could not access gamefile", 2);
		ft_putendl_fd("use kirby= to set the sourcedir", 2);
		return (2);
	}
	ft_strdel(&test);
	i = k_main();
	while (i == 0)
		i = k_main();
	return (0);
}
