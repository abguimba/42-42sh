/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:50:26 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 04:42:58 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_two_arg(char **argv)
{
	if (!argv || !argv[0] || argv[0][0] != '-')
		return (1);
	if (ft_strcmp(argv[0], "-b") == 0 || ft_strcmp(argv[0], "-c") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-d") == 0 || ft_strcmp(argv[0], "-e") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-f") == 0 || ft_strcmp(argv[0], "-g") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-L") == 0 || ft_strcmp(argv[0], "-s") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-p") == 0 || ft_strcmp(argv[0], "-z") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-r") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-S") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-u") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-w") == 0)
		return (0);
	if (ft_strcmp(argv[0], "-x") == 0)
		return (0);
	return (1);
}

int		check_three_arg(char **argv)
{
	if (!argv || !argv[1])
		return (1);
	if (ft_strcmp(argv[1], "=") == 0 || ft_strcmp(argv[1], "!=") == 0)
		return (0);
	if (ft_strcmp(argv[1], "-eq") == 0 || ft_strcmp(argv[1], "-ne") == 0)
		return (0);
	if (ft_strcmp(argv[1], "-ge") == 0 || ft_strcmp(argv[1], "-it") == 0)
		return (0);
	if (ft_strcmp(argv[1], "-le") == 0 || ft_strcmp(argv[1], "-gt") == 0)
		return (0);
	if (ft_strcmp(argv[1], "-lt") == 0)
		return (0);
	return (1);
}
