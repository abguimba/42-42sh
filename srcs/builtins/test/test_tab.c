/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 03:49:52 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 04:24:01 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**copy_tab_minus_one(int argc, char **argv)
{
	char	**av;
	int		i;
	int		a;

	i = 1;
	a = 0;
	av = ft_malloc(sizeof(char *) * (argc + 1));
	while (argv[i])
	{
		av[a] = ft_strdup(argv[i]);
		i++;
		a++;
	}
	av[a] = NULL;
	return (av);
}

int		count_arg(char **taab)
{
	int		i;

	i = 0;
	if (!taab)
		return (1);
	while (taab && taab[0])
	{
		taab++;
		i++;
	}
	return (i);
}
