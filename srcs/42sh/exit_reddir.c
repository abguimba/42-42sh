/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_reddir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 07:28:50 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 02:11:45 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			exit_reddir(void)
{
	if (g_tracking.builtin == 1 || !g_tracking.temp_command)
	{
		g_tracking.builtin = 0;
		return (-1);
	}
	else
		ft_exit2(EXIT_FAILURE);
	return (0);
}
