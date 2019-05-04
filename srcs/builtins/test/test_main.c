/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 03:02:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 01:12:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		one_arg(char **argv)
{
	if (argv[0])
		return (0);
	else
		return (1);
}

int		reverse(int i, int flag)
{
	if (flag == -1)
	{
		if (i == 1)
			return (0);
		if (i == 0)
			return (1);
	}
	return (i);
}

int		return_error(char **argv, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("42sh : Expected unary operator ", 2);
		if (argv[0])
			ft_putstr_fd(argv[0], 2);
		ft_putchar('\n');
		return (2);
	}
	if (i == 2)
	{
		ft_putstr_fd("42sh : Expected binary operator ", 2);
		if (argv[1])
			ft_putstr_fd(argv[1], 2);
		ft_putchar('\n');
		return (2);
	}
	free_tab(argv);
	return (2);
}

int		test_parse(int argc, char **argv)
{
	if (argc == 0)
		return (1);
	if (argc == 1)
		return (one_arg(argv));
	if (argc == 2)
	{
		if (check_two_arg(argv) == 1)
			return (return_error(argv, 1));
		return (two_arg(argv, 1));
	}
	if (argc == 3)
	{
		if (check_three_arg(argv) == 1)
			return (return_error(argv, 2));
		return (three_arg(argv));
	}
	ft_putendl_fd("Too many arguments", 2);
	return (1);
}

int		main_test(int flag, int i, int argc, char **n)
{
	char	**argv;

	argc = count_arg(g_tracking.g_tab_exec);
	argv = g_tracking.g_tab_exec;
	if (!argv || !argv[1] || argv[1][0] == '\0')
		return (1);
	if (!argv[2])
		return (0);
	argv = copy_tab_minus_one(argc, argv);
	argc--;
	if (argc < 1)
		return (return_error(argv, 0));
	if (ft_strcmp(argv[0], "!") == 0)
	{
		n = copy_tab_minus_one(argc, argv);
		free_tab(argv);
		argc--;
		argv = n;
		n = NULL;
		flag = -1;
	}
	i = test_parse(argc, argv);
	i = reverse(i, flag);
	free_tab(argv);
	return (i);
}
