/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hassantest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 19:07:42 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/21 14:48:51 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		history(void)
{
	char	**av;
	int		i;

	i = 0;
	av = g_tracking.g_tab_exec;
	// while (av[i])
	// {
	// 	ft_putendl(av[i]);
	// 	i++;
	// }
	history_builtin();
	return (0);
}
