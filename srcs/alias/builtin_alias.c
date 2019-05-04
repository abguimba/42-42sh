/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 03:18:25 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 05:05:23 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		alias_print_error(char *alias)
{
	if (!alias)
		return (1);
	ft_putstr_fd("alias: ", 2);
	ft_putstr_fd(alias, 2);
	ft_putendl_fd(" : Not found", 2);
	return (1);
}

int		alias_add_error(char *alias)
{
	if (!alias)
		return (1);
	ft_putstr_fd("forbidden char in alias : ", 2);
	ft_putendl_fd(alias, 2);
	return (1);
}

int		search_eq(char *alias)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!alias)
		return (-1);
	if (alias[0] == '=')
		return (0);
	while (alias[i])
	{
		if (alias[i] == '=')
			flag++;
		i++;
	}
	return (flag);
}
