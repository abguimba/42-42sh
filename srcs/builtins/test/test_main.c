/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 03:02:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
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

int		test_parse(int argc, char **argv)
{
	if (argc == 0)
		return (1);
	if (argc == 1)
		return (one_arg(argv));
	if (argc == 2)
		return (two_arg(argv, 1));
	if (argc == 3)
		return (three_arg(argv));
	ft_putendl_fd("Too many arguments", 2);
	return (-1);
}

int		main_test(int flag)
{
	int		i;
	int		argc;
	char	**argv;
	char	**not;

	not = NULL;
	argc = count_arg(g_tracking.g_tab_exec);
	argv = g_tracking.g_tab_exec;
	argv = copy_tab_minus_one(argc, argv);
	argc--;
	if (argc < 1)
		return (1);
	if (ft_strcmp(argv[0], "!") == 0)
	{
		not = copy_tab_minus_one(argc, argv);
		free_tab(argv);
		argc--;
		argv = not;
		flag = -1;
	}
	i = test_parse(argc, argv);
	i = reverse(i, flag);
	free_tab(argv);
	return (i);
}
