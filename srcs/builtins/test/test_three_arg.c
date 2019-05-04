/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_three_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 05:31:34 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 03:20:26 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			string_test(char **argv)
{
	if (ft_strcmp(argv[1], "=") == 0)
	{
		if (ft_strcmp(argv[0], argv[2]) == 0)
			return (0);
		if (ft_strlen(argv[0]) == 0 && ft_strlen(argv[2]) == 0)
			return (0);
	}
	if (ft_strcmp(argv[1], "!=") == 0)
	{
		if (ft_strlen(argv[0]) == 0 && ft_strlen(argv[2]) == 0)
			return (1);
		if (ft_strcmp(argv[0], argv[2]) != 0)
			return (0);
		if (ft_strlen(argv[0]) != ft_strlen(argv[2]))
			return (0);
	}
	return (1);
}

long		get_nbr(char *str)
{
	if (!str)
		return (0);
	if (ft_isinteg(str) != 0)
	{
		ft_putstr("expected integer : ");
		ft_putendl(str);
		return (2147483648);
	}
	return (ft_atoi(str));
}

int			math_test(char **argv, long i, long j)
{
	if (i > 2147483647 || j > 2147483647)
		return (1);
	if (ft_strcmp(argv[1], "-eq") == 0)
		if (j == i)
			return (0);
	if (ft_strcmp(argv[1], "-ne") == 0)
		if (j != i)
			return (0);
	if (ft_strcmp(argv[1], "-ge") == 0)
		if (i >= j)
			return (0);
	if (ft_strcmp(argv[1], "-gt") == 0)
		if (i > j)
			return (0);
	if (ft_strcmp(argv[1], "-it") == 0)
		if (i < j)
			return (0);
	if (ft_strcmp(argv[1], "-le") == 0)
		if (i <= j)
			return (0);
	if (ft_strcmp(argv[1], "-lt") == 0)
		if (i < j)
			return (0);
	return (1);
}

int			three_arg(char **argv)
{
	int		i;

	i = 1;
	if (ft_strcmp(argv[1], "=") == 0 || ft_strcmp(argv[1], "!=") == 0)
		return (string_test(argv));
	if (ft_strcmp(argv[1], "-eq") == 0 || ft_strcmp(argv[1], "-ne") == 0
	|| ft_strcmp(argv[1], "-ge") == 0 || ft_strcmp(argv[1], "-it") == 0
	|| ft_strcmp(argv[1], "-le") == 0 || ft_strcmp(argv[1], "-gt") == 0
	|| ft_strcmp(argv[1], "-lt") == 0)
		return (math_test(argv, get_nbr(argv[0]), get_nbr(argv[2])));
	ft_putendl_fd("too many arguments", 2);
	return (i);
}
